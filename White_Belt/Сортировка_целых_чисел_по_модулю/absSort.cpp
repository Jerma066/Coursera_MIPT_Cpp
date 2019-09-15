//============================================================================
// Name        : absSort.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

bool Compare(int a, int b)
{
	return abs(a) < abs(b);
}

void PrintVect(const vector<int>& vect)
{
	for (int j = 0; j < vect.size(); j++)
	{
		cout << vect[j] << " ";
	}
}

int main() {

	int N, i, number;
	vector<int> A;

	cin >> N;

	for(i = 0; i < N; i++)
	{
		cin >> number;
		A.push_back(number);
	}

	sort(A.begin(), A.end(), Compare);

	PrintVect(A);

	return 0;
}



