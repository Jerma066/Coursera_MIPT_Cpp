#include "query.h"

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
