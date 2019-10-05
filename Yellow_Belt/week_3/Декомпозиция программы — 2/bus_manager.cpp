#include "bus_manager.h"

using namespace std;


void BusManager::AddBus(const string& bus, const vector<string>& stops) {
  buses_to_stops[bus] = stops;
  
  for (const auto& stop : stops) {
	  stops_to_buses[stop].push_back(bus);
  }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
	BusesForStopResponse answer;
	if (stops_to_buses.count(stop) > 0) {
		answer.buses = stops_to_buses.at(stop);
	}
	return answer;
}
	
StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
	
	vector<pair<string, vector<string>>> answer;
	if (buses_to_stops.count(bus) > 0) {
		for (const auto& stop : buses_to_stops.at(bus)) {
			answer.push_back(make_pair(stop, stops_to_buses.at(stop)));
		}
	}
	
	return StopsForBusResponse {bus ,answer};
}


AllBusesResponse BusManager::GetAllBuses() const {
	AllBusesResponse answer;
	answer.allbuses = buses_to_stops;
	return answer;
}
  
  

