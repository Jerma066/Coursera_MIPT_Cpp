//============================================================================
// Name        : binSystem.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	vector<int> result;
	int n, mod;
	string a;

	cin >> n;

	do
	{
		mod = n % 2;
		result.push_back(mod);

		n = n / 2;

	}while(n != 0);

	for(int i = result.size()-1; i>=0; i--)
	{
		cout << result[i];
	}



	return 0;
}
