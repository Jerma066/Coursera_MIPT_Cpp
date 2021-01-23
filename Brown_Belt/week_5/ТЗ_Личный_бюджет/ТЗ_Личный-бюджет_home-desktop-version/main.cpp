#include "budget.h"

#include <iostream>

int main() {
	size_t n;
	std::cin >> n;
	BudgetManager bm;
	bm.Process(n, std::cin);
	return 0;
}
