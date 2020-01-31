#include "database.h"

void Database::Add(const Date& date, const string& event) {
    if (dateBase[date].find(event) == dateBase[date].end()) {
        dateBase[date].insert(event);
        dbQueue[date].push_back(event);
    }
}

ostream& Database::Print(ostream& stream) const{
    for (auto item : dbQueue) {
        for (auto el : item.second) {
            stream << item.first << " " << el << endl;
        }
    }
    return stream;
}

vector<pair<Date, string>> Database::FindIf(function<bool(Date, string)> predicate) const {
    auto copyBase = dbQueue;
    vector<pair<Date, string>> result;

    for (auto& el : copyBase) {
        auto it = stable_partition(el.second.begin(), el.second.end(), [predicate, el](const string& str){
            return !predicate(el.first, str);
        });

        for (auto i = it; i != el.second.end(); i++) {
            result.push_back(make_pair(el.first, *i));
        }
    }
    return result;
};

ostream& operator << (ostream& os, const pair<Date, string>& input ) {
    os << input.first << " " << input.second;
    return os;
}

ostream& operator << (ostream& os, const map<Date, set<string>> input) {
    for (const auto& i : input) {
        for (const auto& j : i.second) {
            cout << i.first << " " << j << endl;
        }
    }
    return os;
}

int Database::RemoveIf(function<bool(Date, string)> predicate){
    int count = 0;
    vector<Date> keysForDel;
    for (auto& el : dbQueue) {
        auto it = stable_partition(el.second.begin(), el.second.end(), [predicate, el](const string& str) {return !predicate(el.first, str);});

        for (auto deleter = --el.second.end(); deleter >= it; deleter--) {
            el.second.erase(deleter);
            count++;
        }

        if (el.second.size() != 0) {
            dateBase[el.first] = set<string>(el.second.begin(), el.second.end());
        }
        else {
            keysForDel.push_back(el.first);
        }
    }

    for (const auto& i : keysForDel ) {
        dbQueue.erase(i);
        dateBase.erase(i);
    }

    return  count;
}

string Database::Last(Date date) const{
    stringstream event;
    if (dateBase.empty() || date < dbQueue.begin()->first) {
        throw invalid_argument("date < all existing");
    }

    auto it = dbQueue.upper_bound(date);
    if (!(--it)->second.empty()) {
        event << it->first << " " << (dbQueue.at(it->first).back());
    }
    return event.str();
}