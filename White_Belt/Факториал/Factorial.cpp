//============================================================================
// Name        : Factorial.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int Factorial(int a)
{
	int fact = 1;

	if (a < 0)
	{
		return 1;
	}
	else
	{
		while (a!=0)
		{
			fact *= a;
			a--;
		}
	}

	return fact;
}

int main() {
	int number;

	cin >> number;

	cout << Factorial(number);

	return 0;
}
