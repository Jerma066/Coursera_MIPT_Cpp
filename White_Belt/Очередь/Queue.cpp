//============================================================================
// Name        : Queue.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void makeComands(vector<bool>& people, vector<int>& answer)
{
	int num;
	string command;
	cin >> command;

	if (command == "WORRY")
	{
		cin >> num;
		people[num] = true;
	}

	if (command == "QUIET")
	{
		cin >> num;
		people[num] = false;
	}

	if (command == "COME")
	{
		cin >> num;
		if (num > 0)
		{
			for (int i = 0; i < num; ++i)
			{
				people.push_back(false);
			}
		}
		else
		{
			num *= -1;
			people.resize(people.size() - num);

		}
	}

	if (command == "WORRY_COUNT")
	{
		int answ = 0;
		for (int i = 0; i < people.size(); ++i)
		{
			if (people[i] == true)
			{
				++answ;
			}
		}

		answer.push_back(answ);
	}
}

void printVector(const vector<int>& vect)
{
	for(int i = 0; i < vect.size(); i++)
	{
		cout << vect[i] << endl;
	}
}
int main()
{
	int Q;
	cin >> Q;

	vector<int> answ;
	vector<bool> people;

	for (int i = 0; i < Q; ++i)
	{
		makeComands(people, answ);
	}

	printVector(answ);

    return 0;
}




