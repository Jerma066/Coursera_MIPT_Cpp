#pragma once

#include <vector>
#include <string_view>
#include <string>
#include <iostream>
#include <utility>

namespace tools {

std::vector<std::string_view> SplitBy(std::string_view str, char sep);
	
}  // tools

std::ostream& operator<< (std::ostream& output, const std::pair<double, double>& pair);
