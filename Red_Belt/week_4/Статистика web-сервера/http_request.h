#pragma once

#include <string_view>

using namespace std;

struct HttpRequest {
	string_view method, uri, protocol;
};

