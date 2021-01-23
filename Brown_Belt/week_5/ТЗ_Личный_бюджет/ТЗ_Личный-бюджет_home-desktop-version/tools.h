#pragma once

#include <vector>
#include <string_view>
#include <string>

namespace tools {

std::vector<std::string_view> SplitBy(std::string_view str, char sep);
	
}  // tools
