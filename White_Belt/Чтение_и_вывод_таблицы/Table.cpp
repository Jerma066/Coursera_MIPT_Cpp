//============================================================================
// Name        : Table.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {

	vector<int> values;
	ifstream input("input.txt");

	int lines = 0;
	int numbers = 0;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~узнаем первые два элемента~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		input >> lines;
		input.ignore(1);
		input >> numbers;
		input.ignore(1);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	for(int i = 0; i < lines * numbers; i++)
	{
		int a = 0;

		input >> a;

		values.push_back(a);
		input.ignore(1);
	}

	for(int j = 0; j < lines; j++)
	{
		for(int k = 0; k < numbers; k++)
		{
			cout << setw(10) << values[(j*numbers) + k];
			if(k != numbers - 1){
				cout << ' ';
			}
		}
		if(j != (lines - 1)){
			cout << endl;
		}
	}


	return 0;
}
