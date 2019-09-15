//============================================================================
// Name        : compairingOfStrings.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	string str1;
	string str2;
	string str3;
	string min;

	cin >> str1 >> str2 >> str3;

	min = str1;

	if (str2 < min) {min = str2;}
	if (str3 < min) {min = str3;}

	cout << min;

	return 0;
}
