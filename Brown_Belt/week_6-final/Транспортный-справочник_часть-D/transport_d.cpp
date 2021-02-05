#include "test_runner.h"
#include "json.h"

#include <iostream>
#include <cmath>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <tuple>
#include <utility>


static const double rcoef = 3.1415926535 / 180;

struct Coordinate {
	Coordinate() = default;
	
	Coordinate(const Coordinate& crd) :	
		rlat(crd.rlat),
		rlon(crd.rlon)
	{
	}
	
	Coordinate(double latitude, double longitude) {
		rlat = latitude * rcoef;
		rlon = longitude * rcoef;
	}
	
	// Convert strings format " 55.632761, 37.333324"
	Coordinate(std::string_view coordinate) {
		size_t pos = coordinate.find(',');
		rlat = std::stod(std::string(coordinate.substr(1, pos))) * rcoef;
		rlon = std::stod(std::string(coordinate.substr(pos + 2, coordinate.size()))) * rcoef;
	}
	
	Coordinate& operator= (const Coordinate& crd) {
		rlat = crd.rlat;
		rlon = crd.rlon;
		return *this;
	}
	
	static double Distance(const Coordinate& lhs, const Coordinate& rhs) { 
		return std::abs(std::acos(
			std::sin(lhs.rlat) * std::sin(rhs.rlat) +
			std::cos(lhs.rlat) * std::cos(rhs.rlat) *
			std::cos(std::abs(lhs.rlon - rhs.rlon))
		)) * 6371000;
	}
	
	double rlat = -1;
	double rlon = -1;
};

bool operator== (const Coordinate& lhs, const Coordinate& rhs) {
	return (
		std::tie(lhs.rlat, lhs.rlon) ==
		std::tie(rhs.rlat, rhs.rlon)
	);
}

std::ostream& operator<< (std::ostream& output, const Coordinate& crd) {
	output << "{" << crd.rlat << ", " << crd.rlon << "}";
	return output;
}

bool operator== (const std::pair<std::string, std::string>& lhs, const std::pair<std::string, std::string>& rhs) {
	return (
		std::tie(lhs.first, lhs.second) ==
		std::tie(rhs.first, rhs.second)
	);
}

std::ostream& operator<< (std::ostream& output, const std::pair<std::string, std::string>& pair) {
	output << "{" << pair.first << ", " << pair.second << "}";
	return output;
}

struct Hasher {
	size_t operator() (const std::pair<std::string, std::string>& route_s) const{
		size_t x = 43;
		
		size_t a = strhash(route_s.first);
		size_t b = strhash(route_s.second);
		
		return (a*x + b);
	}
	
	std::hash<std::string> strhash;
};

using DistancesHash = typename std::unordered_map<std::pair<std::string, std::string>, int, Hasher>;

std::ostream& operator<< (std::ostream& output, const DistancesHash& dists) {
	output << "{";
	for(auto it = dists.begin(); it != dists.end(); it++) {
		output << "{(" << it->first.first << ", " << it->first.second << ")->" << it->second << "}";
	}

	return output;
}

enum class UOperation {
	STOP,
	BUS,
	NONE
};

std::ostream& operator<< (std::ostream& output, const UOperation& op) {
	switch(op) {
		case UOperation::BUS :
			output << "Bus";
			break;
		case UOperation::STOP :
			output << "Stop"; 
			break;
		case UOperation::NONE :
			output << "None";
			break;
	}
	return output;
}

enum class Stage {
	U, // Update
	P  // Perform
};

struct Instruction {	
	Stage st;
	UOperation op = UOperation::NONE;
	int id = 0;
	std::string name = ""; 
	struct Coordinate crd = Coordinate(0, 0);
	std::vector<std::string> route;
	DistancesHash dists;
};

const std::unordered_map<std::string_view, UOperation> UOperHash = {
	{"Stop", UOperation::STOP},
	{"Bus",  UOperation::BUS}
};

std::vector<std::string> ConvertToRoute(std::vector<Json::Node> stops, bool isRndTrip) {
	std::vector<std::string> res;
	for(auto it = stops.begin(); it != stops.end(); ++it) {
		res.push_back(it->AsString());
	}
	if(!isRndTrip) {
		auto rev_res = res;
		std::reverse(rev_res.begin(), rev_res.end());
		res.insert(res.end(), ++rev_res.begin(), rev_res.end());
	}
	return res;
}

DistancesHash ConvertToDists(std::string_view st_name, std::map<std::string, Json::Node> dists) {
	DistancesHash result;
	for(auto it = dists.begin(); it != dists.end(); ++it) {
		result.insert(std::make_pair(
			std::make_pair(st_name, it->first), 
			it->second.AsInt()
		));
	}
	return result;
}

class BusManager {
public:
	using stop_iter = typename std::unordered_map<std::string, Coordinate>::iterator;
public:
	BusManager() = default;
	
public:
	void Process(std::istream& input) {
		std::map<std::string, Json::Node> all_requests = Json::LoadNode(input).AsMap();

		std::vector<Json::Node> base_requests = all_requests.at("base_requests").AsArray();
		for (auto& it : base_requests) {
			Execute(Decode(it, Stage::U));
		}

		std::vector<Json::Node> stat_requests = all_requests.at("stat_requests").AsArray();
		for (auto& it : stat_requests) {
			Execute(Decode(it, Stage::P));
		}
		PrintNodeVector(output, std::cout);
		std::cout << std::endl;
	}

	Instruction Decode(Json::Node& request, Stage st) const {
		Instruction res;
		auto command = request.AsMap();
		res.st = st;
		res.op = UOperHash.at(command.at("type").AsString());

		if(st == Stage::U) {
			res.name = command.at("name").AsString();
			
			switch (res.op) {
				case UOperation::STOP : { 
					Json::Node elem = command.at("latitude");
					double latitude = elem.HasDouble() ? elem.AsDouble() : static_cast<double>(elem.AsInt()); 
					elem = command.at("longitude");
					double longitude = elem.HasDouble() ? elem.AsDouble() : static_cast<double>(elem.AsInt()); 
					res.crd = Coordinate(latitude, longitude);
					res.dists = ConvertToDists(res.name, command.at("road_distances").AsMap());
					break;
				}
				case UOperation::BUS :
					res.route = ConvertToRoute(command.at("stops").AsArray(), command.at("is_roundtrip").AsBool());
					break;
				case UOperation::NONE :
					break;
			};
		}
		else if(st == Stage::P) {
			res.name = command.at("name").AsString();
			res.id = command.at("id").AsInt();
		}
		
		return res;
	}
	
	void Execute(const Instruction& inst) {
		if(inst.st == Stage::U) {
			switch(inst.op) {
				case UOperation::STOP :
					AddStop(inst.name, inst.crd, inst.dists);
					break;
				case UOperation::BUS :
					AddBus(inst.name, inst.route);
					break;
				case UOperation::NONE :
					break;
			}
		}
		else if(inst.st == Stage::P) {
			switch(inst.op) {
				case UOperation::BUS :
					PrintBusStats(inst.name, inst.id);
					break;
				case UOperation::STOP :
					PrintStopInfo(inst.name, inst.id);
				default:
					break;
			}
		}
	}
	
	void AddStop(std::string_view name, const Coordinate& crd, const DistancesHash& dists = {}) {
		stops_[std::string(name)] = crd;
		if(!dists.empty()) {
			for(auto it = dists.begin(); it != dists.end(); it++) {
				if(distances_.count(it->first) == 0) {
					distances_.insert(*it);
				}
			}
		}
	}
	
	void AddBus(std::string_view name, std::vector<std::string> route) {
		for(auto it = route.begin(); it != route.end(); ++it) {
			auto stop = stops_.find(*it);
			if(stop == stops_.end()) {
				auto iter = stops_.insert({*it, Coordinate()});
				routes_[std::string(name)].push_back(iter.first);
			}
			else {
				routes_[std::string(name)].push_back(stop);
			}
			stops_infos_[*it].insert(std::string(name));
		}
	}
	
	void PrintBusStats(std::string name, int id) {
		std::map<std::string, Json::Node> res;
		res["request_id"] = Json::Node(id);
		auto route = routes_.find(name);
		if(route == routes_.end()) {
			res["error_message"] = Json::Node(std::string("not found"));
		}
		else {
			auto bus = route->second;
			res["stop_count"] = Json::Node(static_cast<int>(bus.size()));
			std::unordered_set<std::string> unique;
			double rlength = 0;
			double arlength = 0;
			for(size_t i = 0; i < bus.size(); ++i) {
				unique.insert(bus[i]->first);
				if(i != bus.size() - 1) {
					auto dist_route = std::make_pair(bus[i]->first, bus[i+1]->first);
					auto rdist_route = std::make_pair(bus[i+1]->first, bus[i]->first);
					rlength += Coordinate::Distance(bus[i]->second, bus[i+1]->second);
					if (distances_.count(dist_route) == 1) {
						arlength += distances_[dist_route];
					} 
					else if (distances_.count(rdist_route) == 1) {
						arlength += distances_[rdist_route];
					}
					else if(!distances_.count(dist_route)) {
						arlength += Coordinate::Distance(bus[i]->second, bus[i+1]->second);
					} 
				}
			}
			res["unique_stop_count"] = Json::Node(static_cast<int>(unique.size()));
			res["route_length"] = Json::Node(arlength);
			if (arlength != rlength)
				res["curvature"] = Json::Node(arlength / rlength);
		}
		output.push_back(Json::Node(res));
	}
	
	void PrintStopInfo(std::string name, int id) {
		std::map<std::string, Json::Node> res;
		res["request_id"] = Json::Node(id);
		
		if(stops_.find(name) == stops_.end()) {
			res["error_message"] = Json::Node(std::string("not found"));
		}
		else {
			std::vector<Json::Node> buses;
			if(stops_infos_[name].size() == 0) {
				res["buses"] = Json::Node(buses);
			}
			else {
				for(auto it = stops_infos_[name].begin(); it != stops_infos_[name].end(); ++it) {
					buses.push_back(Json::Node(*it));
				}
				res["buses"] = Json::Node(buses);
			}
		}
		output.push_back(Json::Node(res));
	}
	
	std::unordered_map<std::string, Coordinate> getStops() const {
		return stops_;
	}
	
	std::unordered_map<std::string, std::vector<stop_iter>> getRoutes() const {
		return routes_;
	}
	
private:
	std::unordered_map<std::string, Coordinate> stops_;
	std::unordered_map<std::string, std::vector<stop_iter>> routes_;
	std::unordered_map<std::string, std::set<std::string>> stops_infos_;
	std::vector<Json::Node> output;
	DistancesHash distances_;
};

// Tests area ----------------------------------------------------------

void TestDistances() {
	{
		Coordinate a(55.611087, 37.20829);
		Coordinate b(55.611087, 37.20829);
	
		double res = 0;
		ASSERT_EQUAL(Coordinate::Distance(a, b), res);
	}
	
	{
		Coordinate a(180, 180);
		Coordinate b(0, 0);
	
		double res = 0;
		ASSERT_EQUAL(Coordinate::Distance(a, b), res);
	}
	
	{
		Coordinate a(180, 180);
		Coordinate b(0, 0);
	
		double res = 0;
		ASSERT_EQUAL(Coordinate::Distance(a, b), res);
	}
}

void TestBusManagerAddStop() {
	BusManager bm;
	bm.AddStop("Dubna", Coordinate(55.611087, 37.20829));
	bm.AddStop("Moscow", Coordinate(60.611087, 40.20829));
	bm.AddStop("Dolgorudny", Coordinate(65.611087, 43.20829));
	std::unordered_map<std::string, Coordinate> stops = bm.getStops();
	std::unordered_map<std::string, Coordinate> cor_res = {
		{"Dubna", Coordinate(55.611087, 37.20829)},
		{"Moscow", Coordinate(60.611087, 40.20829)},
		{"Dolgorudny", Coordinate(65.611087, 43.20829)},
	};
	
	ASSERT_EQUAL(stops, cor_res);
}

void TestBusManagerAddBus() {
	{
		BusManager bm;
		bm.AddStop("Dubna", Coordinate(55.611087, 37.20829));
		bm.AddStop("Moscow", Coordinate(60.611087, 40.20829));
		bm.AddStop("Dolgorudny", Coordinate(65.611087, 43.20829));
		
		std::vector<std::string> route = {"Dubna", "Moscow", "Dolgorudny"};
		bm.AddBus("377", route);
		
		auto routes = bm.getRoutes();
		ASSERT_EQUAL(routes.size(), size_t(1));
		ASSERT_EQUAL(routes["377"].size(), route.size());
		for(size_t i = 0; i < routes["377"].size(); i++) {
			ASSERT_EQUAL(routes["377"][i]->first, route[i]);
		}
	}
}

void Tests() {
	TestRunner tr;
	RUN_TEST(tr, TestDistances);
	RUN_TEST(tr, TestBusManagerAddStop);
	RUN_TEST(tr, TestBusManagerAddBus);
}

//----------------------------------------------------------------------

int main() {
	//Tests();
	BusManager bm;
	bm.Process(std::cin);
	return 0;
}

