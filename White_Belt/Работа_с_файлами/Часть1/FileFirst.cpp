//============================================================================
// Name        : FileFirst.cpp
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
	ifstream input;
	string line;

	input.open("input.txt");

	if(input.is_open()){
		while(getline(input, line)){
			cout << line << endl;
		}
	}
	else{
		cout << "error!" << endl;
	}

	return 0;
}
