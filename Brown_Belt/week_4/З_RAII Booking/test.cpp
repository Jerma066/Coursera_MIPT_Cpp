//#include "old_trip_manager.h"  // со старыми классами все тесты проходят
#include "new_trip_manager.h"

#include "test_runner.h"

#include <stdexcept>

using namespace std;

// Эти определения статических переменных правильнее было бы поместить в
// соответствующий cpp-файл, но мы для простоты разместим их здесь

int FlightProvider::capacity = 0;
int FlightProvider::counter = 0;

int HotelProvider::capacity = 0;
int HotelProvider::counter = 0;

void TestNoOverbooking() {
  FlightProvider::capacity = 100;
  HotelProvider::capacity = 100;
  FlightProvider::counter = 0;
  HotelProvider::counter = 0;
  {
    TripManager tm;
    auto trip = tm.Book({});
  }
  ASSERT_EQUAL(FlightProvider::counter, 0);
  ASSERT_EQUAL(HotelProvider::counter, 0);
}

void TestFlightOverbooking() {
  FlightProvider::capacity = 1;
  HotelProvider::capacity = 100;
  FlightProvider::counter = 0;
  HotelProvider::counter = 0;
  try {
    TripManager tm;
    auto trip = tm.Book({});
  } catch (const runtime_error &) {
    ASSERT_EQUAL(FlightProvider::counter, 0);
    ASSERT_EQUAL(HotelProvider::counter, 0);
    return;
  }
  Assert(false, "Flight overbooking was expected");
}

void TestHotelOverbooking() {
  FlightProvider::capacity = 100;
  HotelProvider::capacity = 0;
  FlightProvider::counter = 0;
  HotelProvider::counter = 0;
  try {
    TripManager tm;
    auto trip = tm.Book({});
  } catch (const runtime_error &ex) {
    ASSERT_EQUAL(FlightProvider::counter, 0);
    ASSERT_EQUAL(HotelProvider::counter, 0);
    return;
  }
  Assert(false, "Hotel overbooking was expected");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoOverbooking);
  RUN_TEST(tr, TestFlightOverbooking);
  RUN_TEST(tr, TestHotelOverbooking);
  return 0;
}
