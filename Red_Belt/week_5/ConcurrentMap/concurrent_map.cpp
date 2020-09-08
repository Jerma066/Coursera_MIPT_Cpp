#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <random>
#include <future>
#include <mutex>

using namespace std;

template <typename T>
T abs(T x){
    return x >= 0 ? x : x*(-1);
}

template <typename K, typename V>
class ConcurrentMap
{
static_assert(std::is_convertible_v<K, uint64_t>, "ConcurrentMap supports only integer keys");

public:
    struct Access{
		Access(const K& key, std::pair<std::mutex, std::map<K,V>>& segment): 
			guard(segment.first), 
			ref_to_value(segment.second[key])
        {
		}
		
        std::lock_guard<std::mutex> guard;
        V& ref_to_value;
    };

    explicit ConcurrentMap(size_t bucket_count): 
		segments(bucket_count)
    {
    }

    Access operator[](const K& key);
    map<K, V> BuildOrdinaryMap();
    
private:
    vector<std::pair<std::mutex, std::map<K, V>>> segments;
};

template <typename K, typename V> 
typename ConcurrentMap<K, V>::Access ConcurrentMap<K, V>::operator[](const K& key){
	auto& segment = segments[abs(key) % segments.size()];
	return { key, segment };
}

template <typename K, typename V>
map<K, V> ConcurrentMap<K, V>::BuildOrdinaryMap() {
	std::map<K, V> result;

	for (auto seg = segments.begin(); seg != segments.end(); seg++){
		auto g = lock_guard<std::mutex>{seg->first};
		result.insert(seg->second.begin(), seg->second.end());
	}

	return result;
}

void RunConcurrentUpdates(
    ConcurrentMap<int, int>& cm, size_t thread_count, int key_count
) {
  auto kernel = [&cm, key_count](int seed) {
    vector<int> updates(key_count);
    iota(begin(updates), end(updates), -key_count / 2);
    shuffle(begin(updates), end(updates), default_random_engine(seed));

    for (int i = 0; i < 2; ++i) {
      for (auto key : updates) {
        cm[key].ref_to_value++;
      }
    }
  };

  vector<future<void>> futures;
  for (size_t i = 0; i < thread_count; ++i) {
    futures.push_back(async(kernel, i));
  }
}

void TestConcurrentUpdate() {
  const size_t thread_count = 3;
  const size_t key_count = 50000;

  ConcurrentMap<int, int> cm(thread_count);
  RunConcurrentUpdates(cm, thread_count, key_count);

  const auto result = cm.BuildOrdinaryMap();
  ASSERT_EQUAL(result.size(), key_count);
  for (auto& [k, v] : result) {
    AssertEqual(v, 6, "Key = " + to_string(k));
  }
}

void TestReadAndWrite() {
  ConcurrentMap<size_t, string> cm(5);

  auto updater = [&cm] {
    for (size_t i = 0; i < 50000; ++i) {
      cm[i].ref_to_value += 'a';
    }
  };
  auto reader = [&cm] {
    vector<string> result(50000);
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] = cm[i].ref_to_value;
    }
    return result;
  };

  auto u1 = async(updater);
  auto r1 = async(reader);
  auto u2 = async(updater);
  auto r2 = async(reader);

  u1.get();
  u2.get();

  for (auto f : {&r1, &r2}) {
    auto result = f->get();
    ASSERT(all_of(result.begin(), result.end(), [](const string& s) {
      return s.empty() || s == "a" || s == "aa";
    }));
  }
}

void TestSpeedup() {
  {
    ConcurrentMap<int, int> single_lock(1);

    LOG_DURATION("Single lock");
    RunConcurrentUpdates(single_lock, 4, 50000);
  }
  {
    ConcurrentMap<int, int> many_locks(100);

    LOG_DURATION("100 locks");
    RunConcurrentUpdates(many_locks, 4, 50000);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConcurrentUpdate);
  RUN_TEST(tr, TestReadAndWrite);
  RUN_TEST(tr, TestSpeedup);
}

