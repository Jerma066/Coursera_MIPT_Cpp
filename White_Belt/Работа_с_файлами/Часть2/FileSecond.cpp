//============================================================================
// Name        : FileSecond.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");

	string line;

	if(input.is_open()){
		while(getline(input, line))
		{
			output << line << endl;
		}
	}
	else{
		cout << "error!" << endl;
	}

	return 0;

	return 0;
}
