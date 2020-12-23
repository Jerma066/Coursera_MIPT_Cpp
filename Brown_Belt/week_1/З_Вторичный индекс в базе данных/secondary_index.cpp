#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <tuple>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

enum class Indices{
	Timestamp,
	Karma
};


class Database {
public:
	bool Put(const Record& record) {
		auto [dbIter, isInserted] = database.insert(
			{record.id, Data {record, {}, {}, {}}}
		);
		
		if(isInserted){
			FillDataElement(dbIter->second);
			return true;
		}
		else{
			return false;
		}
		
		return false;
	}
	
	const Record* GetById(const string& id) const{
		auto dbIter = database.find(id);
		if(dbIter != database.end()){
			return &dbIter->second.record;
		}
		else{
			return nullptr;
		}
	}
	
	bool Erase(const string& id){
		auto dbIter = database.find(id);
		if(dbIter != database.end()){
			CleaDataHistory(dbIter->second);
			database.erase(dbIter);
			return true;
		}
		else{
			return false;
		}
		
		return false;
	}

	template <typename Callback>
	void RangeByTimestamp(int low, int high, Callback callback) const {
		auto itBegin = timestamp_indices.lower_bound(low);
		auto itEnd = timestamp_indices.upper_bound(high);
		for (auto it = itBegin; it != itEnd; ++it) {
			if (!callback(*it->second)) {
				break;
			}
		}
	}

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const {
		auto itBegin = karma_indices.lower_bound(low);
		auto itEnd = karma_indices.upper_bound(high);
		for (auto it = itBegin; it != itEnd; ++it) {
			if (!callback(*it->second)) {
				break;
			}
		}
	}

    template <typename Callback>
    void AllByUser(const string& user, Callback callback) const {
		auto [it_begin, it_end] = user_indices.equal_range(user);
		for (auto it = it_begin; it != it_end; ++it) {
		  if (!callback(*it->second)) {
			break;
		  }
		}
	}

private:
	struct Data{
		Record record;
		multimap<int, const Record*>::iterator tms_ind;
		multimap<int, const Record*>::iterator krm_ind;
		multimap<string, const Record*>::iterator usr_ind;	
	};

	void FillDataElement(Data& data){
		const Record* ptr = &data.record;
		data.tms_ind = timestamp_indices.insert({data.record.timestamp, ptr});
		data.krm_ind = karma_indices.insert({data.record.karma, ptr});
		data.usr_ind = user_indices.insert({data.record.user, ptr});
	}
	
	void CleaDataHistory(Data& data){
		timestamp_indices.erase(data.tms_ind);
		karma_indices.erase(data.krm_ind);
		user_indices.erase(data.usr_ind);
	}
  
private:	
	unordered_map<string, Data> database;
	multimap<int, const Record*> timestamp_indices;
	multimap<int, const Record*> karma_indices;
	multimap<string, const Record*> user_indices;
};


void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}


void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}
