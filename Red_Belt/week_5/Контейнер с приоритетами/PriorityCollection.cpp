#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <deque>
#include <list>
#include "test_runner.h"
using namespace std;


template <typename T>
class PriorityCollection {
public:
    using Id = int;
    using Priority = int;

    Id Add(T object) {
        id_to_data[maxId] = move(object);
        priority_to_id[0].push_back(maxId);
        id_to_priority[maxId] = 0;
        return maxId++;
    }

    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
        IdOutputIt ids_begin) {
        while (range_begin != range_end) {
            *ids_begin++ = Add(move(*range_begin));
            range_begin++;
        }
    }

    bool IsValid(Id id) const {
        return id_to_data.count(id);
    }


    const T& Get(Id id) const {
        return id_to_data.at(id);
    }

    void Promote(Id id) {
        auto prior = id_to_priority[id];
        //priority_to_id[prior + 1].push_back(id);
        auto it_to_insert = upper_bound(begin(priority_to_id[prior + 1]), end(priority_to_id[prior + 1]), id);
        priority_to_id[prior + 1].insert(it_to_insert, id);
        priority_to_id[prior].erase(find(begin(priority_to_id[prior]), end(priority_to_id[prior]), id));
        if (priority_to_id[prior].empty()) {
            priority_to_id.erase(prior);
        }
        id_to_priority[id] = prior + 1;
    }

    pair<const T&, int> GetMax() const {
        auto maxPrior = prev(priority_to_id.end(), 1);
        return  pair<const T&, int>{id_to_data.at(maxPrior->second.back()), maxPrior->first};
    }


    pair<T, int> PopMax() {
        auto maxPrior = prev(priority_to_id.end(), 1);
        auto id = maxPrior->second.back();
        pair<T, int> res = { move(id_to_data[id]), maxPrior->first };
        id_to_data.erase(id);
        id_to_priority.erase(id);
        priority_to_id[maxPrior->first].pop_back();
        if (priority_to_id[maxPrior->first].empty()) {
            priority_to_id.erase(maxPrior->first);
        }
        return res;
    }

private:
    map<Priority, deque<Id>> priority_to_id;
    map<Id, T> id_to_data;
    map<Id, Priority> id_to_priority;
    Id maxId = 0;
};

class StringNonCopyable : public std::string
{
public:
    using std::string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) 
    {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
