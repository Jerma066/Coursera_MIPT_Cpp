#include "tools.h"

namespace tools {
	
std::vector<std::string_view> SplitBy(std::string_view s, char sep) {
	std::vector<std::string_view> result;

	while (!s.empty()) {
		size_t pos = s.find(sep);
		result.push_back(s.substr(0, pos));
		s.remove_prefix(pos != s.npos ? pos + 1 : s.size());
	}

	// NVRO
	return result;
}

}  // tools

std::ostream& operator<< (std::ostream& output, const std::pair<double, double>& pair) {
	output << "(" << pair.first << " : " << pair.second << ")";
	return output;
}
