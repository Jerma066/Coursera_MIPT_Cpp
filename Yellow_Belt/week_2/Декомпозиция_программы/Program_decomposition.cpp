#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string type;
    is >> type;
    
    map <string, QueryType> m =
    {
        {"NEW_BUS", QueryType::NewBus},
        {"BUSES_FOR_STOP", QueryType::BusesForStop},
        {"STOPS_FOR_BUS", QueryType::StopsForBus},
        {"ALL_BUSES", QueryType::AllBuses},
    };
    
    q.type = m[type];
    is.ignore(1);
    switch (q.type) {
        case QueryType::NewBus:
            is >> q.bus;

            int n_of_stops;
            is >> n_of_stops;
            q.stops.clear();
            for (int i = 0; i < n_of_stops; ++i) {	
                string stop;
                is >> stop;
                q.stops.push_back(stop);
            }
            break;
        case QueryType::StopsForBus:
            is >> q.bus;
            break;
        case QueryType::BusesForStop:
            is >> q.stop;
            break; 
        case QueryType::AllBuses:
            break;
    }
    return is;
}

struct BusesForStopResponse {
   vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty()) {
        os << "No stop" << endl;
    } 
    else {
        for (size_t i = 0; i < r.buses.size(); i++) {
            os << r.buses[i] << " ";

        }
        os << endl;
    }
    return os;
}

struct StopsForBusResponse {
  string bus;
  vector<pair<string, vector<string>>> stops_for_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (r.stops_for_buses.empty()){
		os << "No bus" << endl;
	} 
	else {
		for (const auto& stop_and_buses : r.stops_for_buses){
			os << "Stop " << stop_and_buses.first << ":";
			
			if (stop_and_buses.second.size() == 1){
				os << " no interchange" << endl;
			} 
			else{
				for (const auto& bus : stop_and_buses.second){
					if (bus != r.bus){
						os << " " << bus;
					}
				}
			
				os << endl;
			}
		}
	}
	
	return os;
}

struct AllBusesResponse {
	map<string, vector<string>> allbuses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.allbuses.empty()) {
        os << "No buses" << endl;
    } 
    else{
        for (const auto& bus : r.allbuses) {	
            os << "Bus " << bus.first << ":";
            for (const auto& stop : bus.second) {
                os << " " << stop;
            }

			os << endl;
        }
    }
    return os;
}

class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
	  buses_to_stops[bus] = stops;
	  
	  for (const auto& stop : stops) {
		  stops_to_buses[stop].push_back(bus);
	  }
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		BusesForStopResponse answer;
		if (stops_to_buses.count(stop) > 0) {
			answer.buses = stops_to_buses.at(stop);
		}
		return answer;
	}
		
    StopsForBusResponse GetStopsForBus(const string& bus) const {
        
        vector<pair<string, vector<string>>> answer;
        if (buses_to_stops.count(bus) > 0) {
            for (const auto& stop : buses_to_stops.at(bus)) {
                answer.push_back(make_pair(stop, stops_to_buses.at(stop)));
            }
        }
        
        return StopsForBusResponse {bus ,answer};
	}


	AllBusesResponse GetAllBuses() const {
		AllBusesResponse answer;
		answer.allbuses = buses_to_stops;
		return answer;
	}
  
  
private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
};

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
