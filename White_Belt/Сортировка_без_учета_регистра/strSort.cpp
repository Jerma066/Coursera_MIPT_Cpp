//============================================================================
// Name        : strSort.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <algorithm>
using namespace std;

string getLowStr(string a)
{
	int i=0;
	char c;

	for(i = 0; i < a.size(); i++)
	{
		 a[i] = (tolower(a[i]));
	}

	return a;
}

bool Compare(const string& a, const string& b)
{
	return getLowStr(a) < getLowStr(b);
}

void PrintVect(const vector<string>& vect)
{
	for (int j = 0; j < vect.size(); j++)
	{
		cout << vect[j] << " ";
	}
}

int main() {

	int N, i;
	string str;
	vector<string> A;

	cin >> N;

	for(i = 0; i < N; i++)
	{
		cin >> str;
		A.push_back(str);
	}

	sort(A.begin(), A.end(), Compare);

	PrintVect(A);

	return 0;
}

