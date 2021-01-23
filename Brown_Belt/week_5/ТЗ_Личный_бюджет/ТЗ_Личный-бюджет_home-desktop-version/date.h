#pragma once

#include "tools.h"

#include <ctime>
#include <string_view> 
#include <string>
#include <tuple>
#include <array>
#include <iostream>

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
	time_t AsTimestamp() const;
	
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
			else {
				mon_++;
			}
		}
		else {
			day_++;
		}
		
		return *this;
	}
	
public:	
	int year_ = 0;
	int mon_ = 0;
	int day_ = 0;
	
private:
	static const int SECONDS_IN_DAY = 60 * 60 * 24;
};

bool operator== (const Date& lhs, const Date& rhs);
bool operator!= (const Date& lhs, const Date& rhs);
bool operator < (const Date& lhs, const Date& rhs);
std::ostream& operator<< (std::ostream& output, const Date& date);
