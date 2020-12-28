#include "Common.h"

#include <algorithm>
#include <future>
#include <mutex>
#include <unordered_map>

using namespace std;

class LruCache : public ICache {
public:
  LruCache(std::shared_ptr<IBooksUnpacker> books_unpacker,
           const Settings &settings)
      : books_unpacker_(move(books_unpacker)), cache_size(settings.max_memory) {
  }

private:
  struct Entry {
    BookPtr book;
    int rank = 0;
  };

public:
  BookPtr GetBook(const string &book_name) override {
    lock_guard guard(mutex_);
    auto it = b_hash.find(book_name);
    if (it == b_hash.end()) {
      Entry entry;
      entry.book = books_unpacker_->UnpackBook(book_name);
      auto cur_book_size = entry.book->GetContent().size();

      while (cache_used_mem + cur_book_size > cache_size && !b_hash.empty()) {
        EraseLongtimeUsedEntry();
      }

      if (cur_book_size > cache_size) {
        return move(entry.book);
      }

      it = AddEntry(book_name, move(entry));
    }

    it->second.rank = current_rank++;
    return it->second.book;
  }

private:
  void EraseLongtimeUsedEntry() {
    if (b_hash.empty())
      return;

    auto it = std::min_element(
        b_hash.begin(), b_hash.end(),
        [](const unordered_map<string, Entry>::value_type &lhs,
           const unordered_map<string, Entry>::value_type &rhs) {
          return (lhs.second.rank < rhs.second.rank);
        });

    cache_used_mem -= it->second.book->GetContent().size();
    b_hash.erase(it);
  }

  unordered_map<string, Entry>::iterator AddEntry(const string &book_name,
                                                  Entry entry) {
    cache_used_mem += entry.book->GetContent().size();
    return b_hash.insert({book_name, move(entry)}).first;
  }

private:
  std::shared_ptr<IBooksUnpacker> books_unpacker_;
  unordered_map<string, Entry> b_hash;

  size_t cache_size;
  size_t cache_used_mem = 0;
  size_t current_rank = 0;

  mutex mutex_;
};

unique_ptr<ICache> MakeCache(std::shared_ptr<IBooksUnpacker> books_unpacker,
                             const ICache::Settings &settings) {
  return make_unique<LruCache>(move(books_unpacker), settings);
}
