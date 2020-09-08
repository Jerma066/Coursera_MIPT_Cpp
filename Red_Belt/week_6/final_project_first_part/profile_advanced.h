#pragma once

#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

struct TotalDuration {
  string message;
  steady_clock::duration value;

  explicit TotalDuration(const string& msg);
  ~TotalDuration();
};

class AddDuration {
public:
  explicit AddDuration(steady_clock::duration& dest);
  explicit AddDuration(TotalDuration& dest);

  ~AddDuration();

private:
  steady_clock::duration& add_to;
  steady_clock::time_point start;
};

#define MY_UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define MY_UNIQ_ID(lineno) MY_UNIQ_ID_IMPL(lineno)

#define ADD_DURATION(value) \
  AddDuration MY_UNIQ_ID(__LINE__){value};
