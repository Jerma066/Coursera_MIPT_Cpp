//============================================================================
// Name        : Anogramas.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <map>

using namespace std;

void isAnogramas (string word1, string word2)
{
	map<char, int> contentW1;
	map<char, int> contentW2;
	char sym1;
	char sym2;

	for(int i  = 0; i < word1.size(); i++)
	{
		sym1 = word1[i];
		contentW1[sym1]++;
	}

	for(int j  = 0; j < word2.size(); j++)
	{
		sym2 = word2[j];
		contentW2[sym2]++;
	}

	if(contentW1 == contentW2)
	{
		cout << "YES \n";
	}
	else
	{
		cout << "NO \n";
	}




}

int main()
{
	string str1;
	string str2;

	int N;
	cin >> N;

	for(int i = 0; i < N; i++)
	{
		cin >> str1 >> str2;
		isAnogramas(str1, str2);
	}

	return 0;
}
