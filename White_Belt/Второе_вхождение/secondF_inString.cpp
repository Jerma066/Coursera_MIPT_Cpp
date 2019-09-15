//============================================================================
// Name        : secondF_inString.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

using namespace std;

int main() {

	int i, answer;
	string S;

	answer = -2;

	cin>>S;

	for(i = 0; i < S.size(); i++)
	{
		if (S[i] == 'f')
		{
			if(answer == -2)
			{
				answer++;
			}
			else if(answer == -1)
			{
				answer = i;
				break;
			}
		}
	}

	cout << answer;

	return 0;
}
