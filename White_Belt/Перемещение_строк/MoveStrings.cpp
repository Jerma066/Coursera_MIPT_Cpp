//============================================================================
// Name        : MoveStrings.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void MoveStrings(vector<string>& source, vector<string>& destination)
{
	string str;
	for(int i = 0; i < source.size(); i++)
	{
		str = source[i];
		destination.push_back(str);
	}

	source.clear();
}

int main() {


}
