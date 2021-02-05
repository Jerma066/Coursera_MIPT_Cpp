#include "test_runner.h"

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

std::vector<std::string> SplitBy(std::string_view s, std::string_view sep) {
	std::vector<std::string> result;
	while (!s.empty()) {
		size_t pos = s.find(sep);
		result.push_back(std::string(s.substr(0, pos)));
		s.remove_prefix(pos != s.npos ? pos + sep.size() : s.size());
	}
	// NVRO
	return result;
}

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
			output << "Bud";
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
	std::string name = ""; 
	struct Coordinate crd = Coordinate(0, 0);
	std::vector<std::string> route;
	DistancesHash dists;
};

const std::unordered_map<std::string_view, UOperation> UOperHash = {
	{"Stop", UOperation::STOP},
	{"Bus",  UOperation::BUS}
};

std::vector<std::string> ConvertToRoute(std::string_view str) {
	const std::string sep = (str.find('-') != str.npos) ? " - " : " > ";
	std::vector<std::string> res = SplitBy(str.substr(1, str.size()), sep);
	if(sep == " - ") {
		auto rev_res = res;
		std::reverse(rev_res.begin(), rev_res.end());
		res.insert(res.end(), ++rev_res.begin(), rev_res.end());
	}
	return res;
}

std::tuple<std::string, int> CreateDist(std::string_view s) {
	auto pos = s.find('m');
	int dist = std::stoi(std::string(s.substr(0, pos)));
	s.remove_prefix(pos + 5);
	std::string stop = std::string(s.substr(0, s.size()));
	
	return std::make_tuple(stop, dist);
}

DistancesHash ConvertToDists(std::string_view st_name, std::string_view dists) {
	DistancesHash result;
	std::vector<std::string> tokens = SplitBy(dists, ", ");
	for(auto it = tokens.begin(); it != tokens.end(); ++it) {
		auto[name, dist] = CreateDist(*it);
		result.insert(std::make_pair(std::make_pair(st_name, name), dist));
	}
	return result;
}

class BusManager {
public:
	using stop_iter = typename std::unordered_map<std::string, Coordinate>::iterator;
public:
	BusManager() = default;
	
public:
	void Process(size_t Q, std::istream& input, Stage st) {
		std::string buf;
		for (size_t i = 0; i < Q; i++) {
			std::getline(input, buf);
			Execute(Decode(buf, st));
		}
	}

	Instruction Decode(std::string_view command, Stage st) const {
		Instruction res;
		res.st = st;
		size_t pos = command.find(' ');
		res.op = UOperHash.at(command.substr(0, pos));
		command.remove_prefix(pos + 1);

		if(st == Stage::U) {
			pos = command.find(':');
			res.name = command.substr(0, pos);
			command.remove_prefix(pos + 1);
			
			switch (res.op) {
				case UOperation::STOP : 
					if(std::count(command.begin(), command.end(), ',') == 1){
						res.crd = Coordinate(command);
					}
					else {
						auto crd_pos = command.find(',', command.find(',') + 1);
						res.crd = Coordinate(command.substr(0, crd_pos));
						command.remove_prefix(crd_pos + 1);
						res.dists = ConvertToDists(res.name, command);
					}
					break;
				case UOperation::BUS :
					res.route = ConvertToRoute(command.substr(0, command.size()));
					break;
				case UOperation::NONE :
					break;
			};
		}
		else if(st == Stage::P) {
			res.name = command.substr(0, command.size());
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
					PrintBusStats(inst.name, std::cout);
					break;
				case UOperation::STOP :
					PrintStopInfo(inst.name, std::cout);
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
	
	std::ostream& PrintBusStats(std::string name, std::ostream& output) {
		output << "Bus " << name << ": ";
		auto route = routes_.find(name);
		if(route == routes_.end()) {
			output << "not found";
		}
		else {
			auto bus = route->second;
			output << bus.size() << " stops on route, ";
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
			output << unique.size() << " unique stops, ";
			output << arlength << " route length";
			if (arlength != rlength)
				output << ", " << (arlength / rlength) << " curvature";
		}
		return output << std::endl;
	}
	
	std::ostream& PrintStopInfo(std::string name, std::ostream& output) {
		output << "Stop " << name << ": ";
		
		if(stops_.find(name) == stops_.end()) {
			output << "not found";
		}
		else {
			if(stops_infos_[name].size() == 0) {
				output << "no buses";
			}
			else {
				std::string buf = "buses ";
				for(auto it = stops_infos_[name].begin(); it != stops_infos_[name].end(); ++it) {
					buf += (*it + " ");
				}
				buf.pop_back();
				output << buf;
			}
		}
		return output << std::endl;
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

//std::pair<std::string, int> CreateDist(std::string_view s) {
void TestCreateDist() {
	{
		auto [name, dist] = CreateDist("7500m to Rossoshanskaya ulitsa");
		ASSERT_EQUAL(name, "Rossoshanskaya ulitsa");
		ASSERT_EQUAL(dist, 7500);
	}
}

void TestBusManagerDecode() {
	{
		BusManager bm;
		Instruction inst = bm.Decode("Stop Tolstopaltsevo: 55.611087, 37.20829", Stage::U);
		ASSERT_EQUAL(inst.op, UOperation::STOP);
		ASSERT_EQUAL(inst.name, "Tolstopaltsevo");
		ASSERT_EQUAL(inst.crd, Coordinate(55.611087, 37.20829));
	}
	
	{
		BusManager bm;
		Instruction inst = bm.Decode("Stop Marushkino: 55.595884, 37.209755", Stage::U);
		ASSERT_EQUAL(inst.op, UOperation::STOP);
		ASSERT_EQUAL(inst.name, "Marushkino");
		ASSERT_EQUAL(inst.crd, Coordinate(55.595884, 37.209755));
	}
	
	{
		BusManager bm;
		Instruction inst = bm.Decode("Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye", Stage::U);
		std::vector<std::string> res_route =  {
			"Biryulyovo Zapadnoye", "Biryusinka", 
			"Universam", "Biryulyovo Tovarnaya",
			"Biryulyovo Passazhirskaya", "Biryulyovo Zapadnoye"
		};
		ASSERT_EQUAL(inst.op, UOperation::BUS);
		ASSERT_EQUAL(inst.name, "256");
		ASSERT_EQUAL(inst.route, res_route);
	}
	
	{
		BusManager bm;
		Instruction inst = bm.Decode("Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka", Stage::U);
		std::vector<std::string> res_route =  {
			"Tolstopaltsevo", "Marushkino", "Rasskazovka", 
			"Marushkino", "Tolstopaltsevo"
		};
		ASSERT_EQUAL(inst.op, UOperation::BUS);
		ASSERT_EQUAL(inst.name, "750");
		ASSERT_EQUAL(inst.route, res_route);
	}
	
	{
		BusManager bm;
		Instruction inst = bm.Decode("Stop Universam: 55.587655, 37.645687, 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya", Stage::U);
		DistancesHash res_dists = {
			{std::make_pair("Universam", "Rossoshanskaya ulitsa"), 5600},
			{std::make_pair("Universam", "Biryulyovo Tovarnaya"), 900}
		};
		ASSERT_EQUAL(inst.op, UOperation::STOP);
		ASSERT_EQUAL(inst.name, "Universam");
		ASSERT_EQUAL(inst.crd, Coordinate(55.587655, 37.645687));
		ASSERT_EQUAL(inst.dists, res_dists);
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
	RUN_TEST(tr, TestBusManagerDecode);
	RUN_TEST(tr, TestCreateDist);
	RUN_TEST(tr, TestBusManagerAddStop);
	RUN_TEST(tr, TestBusManagerAddBus);
}

//----------------------------------------------------------------------

int main() {
	//Tests();
	
	std::string n;
	std::getline(std::cin, n);
	BusManager bm;
	bm.Process(std::stoi(n), std::cin, Stage::U);
	std::getline(std::cin, n);
	bm.Process(std::stoi(n), std::cin, Stage::P);
	return 0;
}

