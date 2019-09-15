//============================================================================
// Name        : bus_stops_2.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <vector>

using namespace std;

void command(map<vector<string>, int>& routes, vector<string>& newRoute, int& num)
{
	if(routes[newRoute] == 0)
	{
		routes[newRoute] = num;
		cout << "New bus " << num++ << endl;
	}
	else
	{
		cout << "Already exists for " << routes[newRoute] <<endl;
	}
}
int main()
{
	int Q;
	int k;
	string word;
	int num = 1;

	map<vector<string>, int> routes;
	vector<string> newRoute;

	cin >> Q;

	for(int i = 0; i < Q; i++)
	{
		cin >> k;
		for (int j = 0; j < k; j++)
		{
			cin >> word;
			newRoute.push_back(word);
		}

		command(routes, newRoute, num);
		newRoute.clear();
	}



	return 0;
}
