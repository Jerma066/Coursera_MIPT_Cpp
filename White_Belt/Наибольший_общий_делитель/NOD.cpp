//============================================================================
// Name        : NOD.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	int A, B;

	cin >> A >> B;

	while (A != 0 && B != 0)
	{
	    if (A > B)
	    {
	        A = A % B;
	    }
	    else
	    {
	        B = B % A;
	    }


	}
	cout << A + B;
	return 0;
}

