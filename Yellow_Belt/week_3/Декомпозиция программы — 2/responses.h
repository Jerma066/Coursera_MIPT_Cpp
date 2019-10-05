#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct BusesForStopResponse {
   vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
  string bus;
  vector<pair<string, vector<string>>> stops_for_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
	map<string, vector<string>> allbuses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);
