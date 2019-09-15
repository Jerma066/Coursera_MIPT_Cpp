//============================================================================
// Name        : Synonimus.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

void command(map<string, set<string> >& mapOfSynonimus, const string& cmd)
{
	if (cmd == "ADD")
	{
		string word1, word2;
		cin >> word1 >> word2;

		mapOfSynonimus[word2].insert(word1);
		mapOfSynonimus[word1].insert(word2);
	}

	if (cmd == "COUNT")
	{
		string word;
		cin >> word;

		cout << mapOfSynonimus[word].size() << endl;
	}

	if (cmd == "CHECK")
	{
		string word3, word4;
		cin >> word3 >> word4;

		int a;

		a = mapOfSynonimus[word3].count(word4);

		if(a!=0)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
}

int main() {

	int Q;
	map<string, set<string> > mapOfSynonimus;
	string cmd;

	cin >> Q;

	for(int i = 0; i < Q; i++)
	{
		cin >> cmd;
		command(mapOfSynonimus, cmd);
	}

	return 0;
}
