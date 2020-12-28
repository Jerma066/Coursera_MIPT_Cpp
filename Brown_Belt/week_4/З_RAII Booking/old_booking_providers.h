#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class FlightProvider {
public:
  using BookingId = int;

  struct BookingData {
    string city_from;
    string city_to;
    string date;
  };

  BookingId Book(const BookingData &data) {
    if (counter >= capacity) {
      throw runtime_error("Flight overbooking");
    }
    ++counter;
    return counter;
  }

  void Cancel(const BookingId &id) {
    --counter;
    if (counter < 0) {
      throw logic_error("Too many flights have been canceled");
    }
  }

public:
  static int capacity;
  static int counter;
};

class HotelProvider {
public:
  using BookingId = int;

  struct BookingData {
    string city;
    string date_from;
    string date_to;
  };

  BookingId Book(const BookingData &data) {
    if (counter >= capacity) {
      throw runtime_error("Hotel overbooking");
    }
    ++counter;
    return counter;
  }

  void Cancel(const BookingId &id) {
    --counter;
    if (counter < 0) {
      throw logic_error("Too many hotels have been canceled");
    }
  }

public:
  static int capacity;
  static int counter;
};
