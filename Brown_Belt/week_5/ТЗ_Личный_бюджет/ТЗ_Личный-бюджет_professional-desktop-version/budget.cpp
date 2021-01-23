#include "budget.h"

std::ostream& operator<< (std::ostream& output, const Operation& op) {
	switch(op) {
		case Operation::EARM :
			output << "Earn";
			break;
		case Operation::PAY_TAX :
			output << "PayTax"; 
			break;
		case Operation::COMPUTE_INCOME :
			output << "ComputeIncome";
			break;
		case Operation::SPEND :
			output << "Spend";
			break;
	}
	return output;
}

void BudgetManager::Process(size_t Q, std::istream& input) {
	std::string buf;
	for (size_t i = 0; i < Q; i++) {
		std::getline(input, buf);
		if(buf == "") {std::getline(input, buf);}
		Execute(Decode(buf));
	}
}

Instruction BudgetManager::Decode(std::string_view command) const {
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

void BudgetManager::Execute(const Instruction& inst) {
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

void BudgetManager::EarnMoney(const Date& from, const Date& to, int value) {
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

void BudgetManager::PayTaxes(const Date& from, const Date& to, int percent) {
	finance_iter fi = finance.lower_bound(from);
	finance_iter si = finance.upper_bound(to);	
	for (auto it = fi; it != si; ++it) {
		it->second.first *= (static_cast<double>(100 - percent) / 100);
	}
}

double BudgetManager::ComputeIncome(const Date& from, const Date& to) {
	double res = 0;
	finance_iter fi = finance.lower_bound(from);
	finance_iter si = finance.upper_bound(to);
	for (auto it = fi; it != si; ++it) {
		res += it->second.first + it->second.second;
	}
	return res;
}

void BudgetManager::SpendMoney(const Date& from, const Date& to, int value) {
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




