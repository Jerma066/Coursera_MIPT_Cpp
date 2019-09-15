//============================================================================
// Name        : PalindromFilter.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool IsPalindrom(string str)
{
	bool answer = true;

	if (str.size() != 0)
	{
		for (int i = 0; i < (str.size() / 2); i++)
		{
			int j = str.size() - (i+1);
			if (str[i] != str[j])
			{
				answer = false;
				break;
			}
		}
	}

	return answer;
}

vector<string> PalindromFilter(vector<string> words, int minLength)
{
	vector<string> answer;

	for(string str : words)
	{
		if(str.size() >= minLength && IsPalindrom(str))
		{
			answer.push_back(str);
		}
	}

	return answer;
}

int main()
{
	vector<string> result;
	vector<string> words;

	int minLength;

	cin>>minLength;

	result = PalindromFilter(words, minLength);

	for (string word : result){
		cout << word;
	}

	return 0;
}
