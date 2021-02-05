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

std::vector<std::string> SplitRouteBy(std::string_view s, char sep) {
	std::vector<std::string> result;
	while (!s.empty()) {
		size_t pos = s.find(sep);
		result.push_back(std::string(s.substr(1, pos - 2)));
		s.remove_prefix(pos != s.npos ? pos + 1 : s.size());
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
};

const std::unordered_map<std::string_view, UOperation> UOperHash = {
	{"Stop", UOperation::STOP},
	{"Bus",  UOperation::BUS}
};

std::vector<std::string> ConvertToRoute(std::string_view str) {
	const char sep = (str.find('-') != str.npos) ? '-' : '>';
	std::vector<std::string> res = SplitRouteBy(str, sep);
	if(sep == '-') {
		auto rev_res = res;
		std::reverse(rev_res.begin(), rev_res.end());
		res.insert(res.end(), ++rev_res.begin(), rev_res.end());
	}
	return res;
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
					res.crd = Coordinate(command.substr(0, command.size()));
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
					AddStop(inst.name, inst.crd);
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
				default:
					break;
			}
		}
	}
	
	void AddStop(std::string_view name, const Coordinate& crd) {
		stops_[std::string(name)] = crd;
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
			for(size_t i = 0; i < bus.size(); ++i) {
				unique.insert(bus[i]->first);
				if(i != bus.size() - 1) {
					rlength += Coordinate::Distance(bus[i]->second, bus[i+1]->second);
				}
			}
			output << unique.size() << " unique stops, ";
			output << rlength << " route length";
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

