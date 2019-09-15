//============================================================================
// Name        : Recerse.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> Reversed(vector<int> source)
{
	int change;
	int a;

	for(int i = 0; i < source.size()/2; i++)
	{
		a = source.size() - i - 1;

		change = source[i];
		source [i] = source[a];
		source[a] = change;

	}

	return source;
}

int main() {

	vector<int> source;

	source.push_back(1);
	source.push_back(5);
	source.push_back(3);
	source.push_back(4);
	source.push_back(2);

    source = Reversed(source);

    for (int i = 0; i < source.size(); i++)
    {
    	cout << source[i];
    }



}

