//============================================================================
// Name        : quadraticEquation.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>

using namespace std;

int main() {

	double A, B, C;
	double D;
	double X1 = 0 , X2 = 0;

	cin >> A >> B >> C;

	D = B*B - 4*A*C;

	if (D > 0 && A != 0)
	{
		X1 = ((-1)*B + sqrt(D))/(2*A);
		X2 = ((-1)*B - sqrt(D))/(2*A);

		cout << X1 << " " << X2;
	}

	if (D == 0 && A != 0)
	{
		X1 = (-1)*B/(2*A) + 0;
		cout << X1;
	}

	if (A == 0 && B!=0){
		X1 = (-1)*(C/B);
		cout << X1 + 0;
	}


	return 0;
}
