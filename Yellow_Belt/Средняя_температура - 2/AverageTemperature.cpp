//============================================================================
// Name        : AverageTemperature.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Counting Average Temperature in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

using namespace std;

int averageTemperature (const vector<int>& temperatures) {

	long int sum = 0;
	int i, avT;

	for(i=0; i < temperatures.size(); i++)
	{
		sum += temperatures[i];
	}

	avT = sum / static_cast<int>(temperatures.size());

	return avT;

}

void indexPrinting (const vector<int>& temperatures, const int avT) {

	vector<int> indexes;
	int i;

	for (i = 0; i < temperatures.size(); i++)
	{
		if (temperatures[i] > avT)
		{
			indexes.push_back(i);
		}
	}

	cout << indexes.size() << endl;;

	for (i = 0; i < indexes.size(); i++)
	{
		cout << indexes[i] << " ";
	}
}

int main() {

	int n, avT;
	cin >> n;

	vector<int> temperatures(n);

	for(int i = 0; i < n; i++)
	{
		cin >> temperatures[i];
	}

	avT = averageTemperature(temperatures);

	indexPrinting(temperatures, avT);

	return 0;
}
