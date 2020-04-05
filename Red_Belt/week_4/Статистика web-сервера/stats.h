#pragma once

#include "http_request.h"

#include <string_view>
#include <map>

using namespace std;
typedef map<string_view, int> StatsMap;

class Stats {
public:
	Stats();
	void AddMethod(string_view method);
	void AddUri(string_view uri);
	const map<string_view, int>& GetMethodStats() const;
	const map<string_view, int>& GetUriStats() const;
  
private:
	StatsMap methods;
	StatsMap uris;
};

HttpRequest ParseRequest(string_view line);
