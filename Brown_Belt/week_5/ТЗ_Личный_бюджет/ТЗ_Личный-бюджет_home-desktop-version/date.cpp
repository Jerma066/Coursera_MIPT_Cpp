#include "date.h"

time_t Date::AsTimestamp() const {
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

bool operator== (const Date& lhs, const Date& rhs) {
	return (
		std::tie(lhs.year_, lhs.mon_, lhs.day_) ==
		std::tie(rhs.year_, rhs.mon_, rhs.day_)
	);
}

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

std::ostream& operator<< (std::ostream& output, const Date& date) {
	output << "{" << date.year_ << "-" << date.mon_ << "-" << date.day_ << "}";
	return output;
}


