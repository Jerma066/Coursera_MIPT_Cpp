#ifndef __DATABASE_H
#define __DATABASE_H

#include "date.h"
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

class Database {
public:
    void Add(const Date& date, const string& event);
    ostream& Print(ostream& stream) const;
    vector<pair<Date, string>> FindIf(function<bool(Date, string)> ) const;
    int RemoveIf(function<bool(Date, string)>);
    string Last(Date) const;

private:
    map<Date, set<string> > dateBase;
    map<Date, vector<string>> dbQueue;
};

ostream& operator << (ostream& os, const pair<Date, string>& input );
ostream& operator << (ostream& os, const map<Date, set<string>> input);


#endif //__DATABASE_H
