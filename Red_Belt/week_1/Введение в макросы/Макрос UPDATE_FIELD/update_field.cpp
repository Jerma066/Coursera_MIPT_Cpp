#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <numeric>
#include <tuple>
#include <iomanip>
#include <sstream>

using namespace std;

#define UPDATE_FIELD(ticket, field, values)		\
	if(values.count(#field) != 0){				\
		istringstream is(values.at(#field));    \
		is >> ticket.field;                     \
	}

#define SORT_BY(field)                                     \
  [](const AirlineTicket& lhs, const AirlineTicket& rhs) { \
    return lhs.field < rhs.field;                          \
  }


// overload operators for Date and Time:
ostream& operator<<(ostream& os, const Date& date) {
    return os << setw(4) << setfill('0') << date.year << '-'
              << setw(2) << setfill('0') << date.month << '-'
              << setw(2) << setfill('0') << date.day;
}

ostream& operator<<(ostream& os, const Time& time) {
    return os << setw(2) << setfill('0') << time.hours << ':'
              << setw(2) << setfill('0') << time.minutes;
}

istream& operator>>(istream& is, Date& date) {
  is >> date.year;
  is.ignore(1);
  is >> date.month;
  is.ignore(1);
  is >> date.day;
  return is;
}

istream& operator>>(istream& is, Time& time) {
  is >> time.hours;
  is.ignore(1);
  is >> time.minutes;
  return is;
}

bool operator==(const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day)
         == tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Time& lhs, const Time& rhs) {
  return tie(lhs.hours, lhs.minutes)
         == tie(rhs.hours, rhs.minutes);
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
