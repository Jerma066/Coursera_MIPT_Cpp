#pragma once

#include "iterator_range.h"

#include <string_view>
#include <sstream>
#include <vector>
using namespace std;

template <typename Container>
string Join(char c, const Container& cont) {
  ostringstream os;
  for (const auto& item : Head(cont, cont.size() - 1)) {
    os << item << c;
  }
  os << *rbegin(cont);
  return os.str();
}

string_view Strip(string_view s);
vector<string_view> SplitBy(string_view s, char sep);
void LeftStrip(string_view& sv);
string_view ReadToken(string_view& sv);

vector<string_view> SplitIntoWordsView(string_view str);
