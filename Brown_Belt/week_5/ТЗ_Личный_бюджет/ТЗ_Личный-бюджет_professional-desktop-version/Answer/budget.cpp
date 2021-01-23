#include <ctime>
#include <string_view> 
#include <string>
#include <tuple>
#include <array>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <map>
#include <vector>
#include <utility>

namespace tools {
	
std::vector<std::string_view> SplitBy(std::string_view s, char sep) {
	std::vector<std::string_view> result;
	while (!s.empty()) {
		size_t pos = s.find(sep);
		result.push_back(s.substr(0, pos));
		s.remove_prefix(pos != s.npos ? pos + 1 : s.size());
	}
	// NVRO
	return result;
}

}  // tools

const std::array<int, 13> MonthLegth = {
	0,
	31, 28, 31, 30, 31, 30, 
	31, 31, 30, 31, 30, 31
};

struct Date {	
public:
	Date() = default;

	Date(std::string_view date) {
		std::vector<std::string_view> date_elems = tools::SplitBy(date, '-');
		year_ = std::stoi(std::string(date_elems[0]));
		mon_ = std::stoi(std::string(date_elems[1]));
		day_ = std::stoi(std::string(date_elems[2]));
	}
	
	Date(const Date& date) :
		year_(date.year_),
		mon_(date.mon_),
		day_(date.day_)
	{
	}
	
public:
	time_t AsTimestamp() const {
		std::tm t;
		t.tm_sec   = 0;
		t.tm_min   = 0;
		t.tm_hour  = 0;
		t.tm_mday  = day_;
		t.tm_mon   = mon_ - 1;
		t.tm_year  = year_ - 1900;
		t.tm_isdst = 0;
		return mktime(&t);
	}
	
	static int ComputeDaysDiff(const Date& date_from, const Date& date_to) {
		return (date_to.AsTimestamp() - date_from.AsTimestamp()) / SECONDS_IN_DAY;
	}
	
	static int GetNumOfDays(int mon, int year) {
		if((mon == 2) && !(year % 4 != 0 || ((year % 100 == 0) && (year % 400 != 0)))) {
			return 29;
		}
		return MonthLegth[mon];
	}
	
	static Date nextDay(Date date) {
		return date.nextDay();
	}
	
	Date nextDay() {
		if (day_ == GetNumOfDays(mon_, year_)) {
			day_ = 1;
			if (mon_ == 12) {
				mon_ = 1; 
				year_++;
			}
			else {mon_++;}
		}
		else {day_++;}
		return *this;
	}
	
public:	
	int year_ = 0;
	int mon_ = 0;
	int day_ = 0;
	
private:
	static const int SECONDS_IN_DAY = 60 * 60 * 24;
};

bool operator!= (const Date& lhs, const Date& rhs) {
	return (
		std::tie(lhs.year_, lhs.mon_, lhs.day_) !=
		std::tie(rhs.year_, rhs.mon_, rhs.day_)
	);
}

bool operator< (const Date& lhs, const Date& rhs) {
	return (
		std::tie(lhs.year_, lhs.mon_, lhs.day_) < 
		std::tie(rhs.year_, rhs.mon_, rhs.day_)
	);
}

enum class Operation {
	NONE,
	EARM,
	PAY_TAX,
	COMPUTE_INCOME,
	SPEND
};

struct Instruction {	
	Operation op = Operation::NONE;
	Date from;
	Date to;
	int value = -1;
};

class BudgetManager {
public:
	BudgetManager() = default;

public:
	void Process(size_t Q, std::istream& input) {
		std::string buf;
		for (size_t i = 0; i < Q; i++) {
			std::getline(input, buf);
			if(buf == "") {std::getline(input, buf);}
			Execute(Decode(buf));
		}
	}
	
	Instruction Decode(std::string_view command) const {
		Instruction res;
		std::vector<std::string_view> tokens = tools::SplitBy(command, ' ');
		
		res.from = tokens[1];
		res.to = tokens[2];
		
		std::string cmd = std::string(tokens[0]);
		if(cmd == "Earn") {
			res.op = Operation::EARM;
			res.value = std::stoi(std::string(tokens[3]));
		}
		else if (cmd == "PayTax") {
			res.op = Operation::PAY_TAX;
			res.value = std::stoi(std::string(tokens[3]));
		}
		else if (cmd == "ComputeIncome") {
			res.op = Operation::COMPUTE_INCOME;
		}
		else if (cmd == "Spend") {
			res.op = Operation::SPEND;
			res.value = std::stoi(std::string(tokens[3]));
		}
		
		return res;
	}
	
	void Execute(const Instruction& inst) {
		switch (inst.op) {
			case Operation::EARM :
				EarnMoney(inst.from, inst.to, inst.value);
				break;
			case Operation::PAY_TAX :
				PayTaxes(inst.from, inst.to, inst.value);
				break;
			case Operation::COMPUTE_INCOME :
				std::cout << std::setprecision(25) << ComputeIncome(inst.from, inst.to) << std::endl;
				break;
			case Operation::SPEND:
				SpendMoney(inst.from, inst.to, inst.value);
				break;
			case Operation::NONE :
				break;
		}
	}

	void EarnMoney(const Date& from, const Date& to, int value) {
		int dnum = Date::ComputeDaysDiff(from, to);
		double val_per_day = static_cast<double>(value) / (dnum + 1);
		Date cur_day = from;
		for(int i = 0; i < dnum + 1; i++) {
			if (finance.count(cur_day) == 1) {
				finance[cur_day].first += val_per_day;
			}
			else {
				finance[cur_day] = std::make_pair(val_per_day, 0);
			}
			cur_day.nextDay();
		}
	}

	void PayTaxes(const Date& from, const Date& to, int percent) {
		finance_iter fi = finance.lower_bound(from);
		finance_iter si = finance.upper_bound(to);	
		for (auto it = fi; it != si; ++it) {
			it->second.first *= (static_cast<double>(100 - percent) / 100);
		}
	}

	double ComputeIncome(const Date& from, const Date& to) {
		double res = 0;
		finance_iter fi = finance.lower_bound(from);
		finance_iter si = finance.upper_bound(to);
		for (auto it = fi; it != si; ++it) {
			res += it->second.first + it->second.second;
		}
		return res;
	}
	
	void SpendMoney(const Date& from, const Date& to, int value) {
		int dnum = Date::ComputeDaysDiff(from, to);
		double val_per_day = static_cast<double>(value) / (dnum + 1);
		Date cur_day = from;
		for(int i = 0; i < dnum + 1; i++) {
			if (finance.count(cur_day) == 1) {
				finance[cur_day].second -= val_per_day;
			}
			else {
				finance[cur_day] = std::make_pair(0, -val_per_day);
			}
			cur_day.nextDay();
		}
	}

	
public:
	std::map<Date, std::pair<double, double>> getFinance() {
		return finance;
	}

private:
	using finance_iter = typename std::map<Date, std::pair<double, double>>::iterator;
	std::map<Date, std::pair<double, double>> finance;
};

int main() {
	size_t n;
	std::cin >> n;
	BudgetManager bm;
	bm.Process(n, std::cin);
	return 0;
}

