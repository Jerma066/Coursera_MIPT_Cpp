 //============================================================================
// Name        : Unique.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
	set<string> words;
	int Q;
	string word;
	cin >> Q;

	for(int i = 0; i < Q; i++)
	{
		cin >> word;
		words.insert(word);
	}

	cout << words.size();
	return 0;
}
