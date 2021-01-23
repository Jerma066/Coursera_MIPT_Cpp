#include "test_runner.h"
#include "../date.h"
#include "../budget.h"

#include <iostream>
#include <string>
#include <tuple>
#include <utility>

void TestStringParcer() {
	std::vector<std::string_view> date = tools::SplitBy("2020-01-02", '-');
	std::vector<std::string_view> res = {"2020", "01", "02"};
	ASSERT_EQUAL(date, res);
}

void TestDateConstructor() {
    {
    	Date date("2020-01-02");    	
		ASSERT_EQUAL(date.year_, 2020);
		ASSERT_EQUAL(date.mon_, 1);
		ASSERT_EQUAL(date.day_, 2);
	}
	
	{
    	Date date("2000-01-16");
		ASSERT_EQUAL(date.year_, 2000);
		ASSERT_EQUAL(date.mon_, 1);
		ASSERT_EQUAL(date.day_, 16);
	}
}

void TestMonthLength() {
	{
		int dnum = Date::GetNumOfDays(1, 2020);
		ASSERT_EQUAL(dnum, 31);
	}
	
	{
		int dnum = Date::GetNumOfDays(2, 2020);
		ASSERT_EQUAL(dnum, 29);
	}
	
	{
		int dnum = Date::GetNumOfDays(2, 2001);
		ASSERT_EQUAL(dnum, 28);
	}
}

void TestNextDate() {
	{
		Date date("2020-01-02");
		Date res("2020-01-03");
		ASSERT_EQUAL(Date::nextDay(date), res);
	}
	
	{
		Date date("2020-02-28");
		Date res("2020-02-29");
		ASSERT_EQUAL(Date::nextDay(date), res);
	}
	
	{
		Date date("2019-02-28");
		Date res("2019-03-01");
		ASSERT_EQUAL(Date::nextDay(date), res);
	}
	
	{
		Date date("1998-10-16");
		Date res("1998-10-17");
		ASSERT_EQUAL(Date::nextDay(date), res);
	}
	
	{
		Date date("2020-12-31");
		Date res("2021-01-01");
		ASSERT_EQUAL(Date::nextDay(date), res);
	}	
}

void TestBudgetManagerDecode() {
	{
		BudgetManager bm;
		std::string oper = "Earn 2000-01-02 2000-01-06 20";
		Instruction res = bm.Decode(oper);
		Instruction cor_ans = {Operation::EARM, Date("2000-01-02"), Date("2000-01-06"), 20};
		
		ASSERT_EQUAL(res.op, cor_ans.op);
		ASSERT_EQUAL(res.from, cor_ans.from);
		ASSERT_EQUAL(res.to, cor_ans.to);
		ASSERT_EQUAL(res.value, cor_ans.value);
	}
	
	{
		BudgetManager bm;
		std::string oper = "ComputeIncome 2000-01-01 2001-01-01";
		Instruction res = bm.Decode(oper);
		Instruction cor_ans = {Operation::COMPUTE_INCOME, Date("2000-01-01"), Date("2001-01-01"), -1};
		
		ASSERT_EQUAL(res.op, cor_ans.op);
		ASSERT_EQUAL(res.from, cor_ans.from);
		ASSERT_EQUAL(res.to, cor_ans.to);
		ASSERT_EQUAL(res.value, cor_ans.value);
	}
	
	{
		BudgetManager bm;
		std::string oper = "PayTax 2000-01-02 2000-01-03 13";
		Instruction res = bm.Decode(oper);
		Instruction cor_ans = {Operation::PAY_TAX, Date("2000-01-02"), Date("2000-01-03"), 13};
		
		ASSERT_EQUAL(res.op, cor_ans.op);
		ASSERT_EQUAL(res.from, cor_ans.from);
		ASSERT_EQUAL(res.to, cor_ans.to);
		ASSERT_EQUAL(res.value, cor_ans.value);
	}	
}

void TestBudgetManagerEarn() {
	{
		BudgetManager bm;
		bm.EarnMoney(Date("2000-01-01"), Date("2000-01-02"), 20);
		std::map<Date, std::pair<double, double>> res = bm.getFinance();
		std::map<Date, std::pair<double, double>> cor_ans = {
			{Date("2000-01-01"), std::make_pair(10, 0)}, 
			{Date("2000-01-02"), std::make_pair(10, 0)}
		};
		ASSERT_EQUAL(res, cor_ans);
	}
	
	{
		BudgetManager bm;
		bm.EarnMoney(Date("2000-01-01"), Date("2000-01-06"), 30);
		std::map<Date, std::pair<double, double>> res = bm.getFinance();
		std::map<Date, std::pair<double, double>> cor_ans = {
			{Date("2000-01-01"), std::make_pair(5, 0)}, {Date("2000-01-02"), std::make_pair(5, 0)}, 
			{Date("2000-01-03"), std::make_pair(5, 0)}, {Date("2000-01-04"), std::make_pair(5, 0)}, 
			{Date("2000-01-05"), std::make_pair(5, 0)}, {Date("2000-01-06"), std::make_pair(5, 0)}
		};
		ASSERT_EQUAL(res, cor_ans);
	}

	{
		BudgetManager bm;
		bm.EarnMoney(Date("2000-12-29"), Date("2001-01-03"), 30);
		std::map<Date, std::pair<double, double>> res = bm.getFinance();
		std::map<Date, std::pair<double, double>> cor_ans = {
			{Date("2000-12-29"), std::make_pair(5, 0)}, {Date("2000-12-30"), std::make_pair(5, 0)}, 
			{Date("2000-12-31"), std::make_pair(5, 0)}, {Date("2001-01-01"), std::make_pair(5, 0)}, 
			{Date("2001-01-02"), std::make_pair(5, 0)}, {Date("2001-01-03"), std::make_pair(5, 0)}
		};
		ASSERT_EQUAL(res, cor_ans);
	}
} 

void TestBudgetManagerPayTax() {
	{
		BudgetManager bm;
		bm.EarnMoney(Date("2000-01-01"), Date("2000-01-02"), 20);
		bm.PayTaxes(Date("2000-01-01"), Date("2000-01-02"), 13);
		std::map<Date, std::pair<double, double>> res = bm.getFinance();
		std::map<Date, std::pair<double, double>> cor_ans = {
			{Date("2000-01-01"), std::make_pair(8.7, 0)}, 
			{Date("2000-01-02"), std::make_pair(8.7, 0)}
		};
		ASSERT_EQUAL(res, cor_ans);
	}
	
	{
		BudgetManager bm;
		bm.EarnMoney(Date("2000-01-01"), Date("2000-01-06"), 60);
		bm.PayTaxes(Date("2000-01-02"), Date("2000-01-05"), 13);
		std::map<Date, std::pair<double, double>> res = bm.getFinance();
		std::map<Date, std::pair<double, double>> cor_ans = {
			{Date("2000-01-01"), std::make_pair(10, 0)},  {Date("2000-01-02"), std::make_pair(8.7, 0)}, 
			{Date("2000-01-03"), std::make_pair(8.7, 0)}, {Date("2000-01-04"), std::make_pair(8.7, 0)}, 
			{Date("2000-01-05"), std::make_pair(8.7, 0)}, {Date("2000-01-06"), std::make_pair(10, 0) }
		};
		ASSERT_EQUAL(res, cor_ans);
	}
	
	{
		BudgetManager bm;
		bm.EarnMoney(Date("2000-12-29"), Date("2001-01-03"), 60);
		bm.PayTaxes(Date("2000-12-26"), Date("2001-01-05"), 13);
		std::map<Date, std::pair<double, double>> res = bm.getFinance();
		std::map<Date, std::pair<double, double>> cor_ans = {
			{Date("2000-12-29"), std::make_pair(8.7, 0)}, {Date("2000-12-30"), std::make_pair(8.7, 0)}, 
			{Date("2000-12-31"), std::make_pair(8.7, 0)}, {Date("2001-01-01"), std::make_pair(8.7, 0)}, 
			{Date("2001-01-02"), std::make_pair(8.7, 0)}, {Date("2001-01-03"), std::make_pair(8.7, 0)}
		};
		ASSERT_EQUAL(res, cor_ans);
	}
} 

void TestBudgetManagerComputeIncome() {
	{
		BudgetManager bm;
		bm.EarnMoney(Date("2000-01-01"), Date("2000-01-02"), 20);
		double res = bm.ComputeIncome(Date("2000-01-01"), Date("2000-01-02"));
		ASSERT_EQUAL(res, 20);
	}

	{
		BudgetManager bm;
		bm.EarnMoney(Date("2000-01-01"), Date("2000-01-06"), 60);
		double res = bm.ComputeIncome(Date("2000-01-02"), Date("2000-01-05"));
		ASSERT_EQUAL(res, 40);
	}
	
	{
		BudgetManager bm;
		bm.EarnMoney(Date("2000-12-29"), Date("2001-01-03"), 60);
		double res = bm.ComputeIncome(Date("2000-12-26"), Date("2001-01-05"));
		ASSERT_EQUAL(res, 60);
	}
} 

int main() {
	TestRunner tr;

	RUN_TEST(tr, TestStringParcer);
	RUN_TEST(tr, TestDateConstructor);
	RUN_TEST(tr, TestMonthLength);
	RUN_TEST(tr, TestNextDate);
	RUN_TEST(tr, TestBudgetManagerDecode);
	RUN_TEST(tr, TestBudgetManagerEarn);
	RUN_TEST(tr, TestBudgetManagerPayTax);
	RUN_TEST(tr, TestBudgetManagerComputeIncome);
		
	return 0;
}
