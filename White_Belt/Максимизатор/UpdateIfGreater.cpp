//============================================================================
// Name        : UpdateIfGreater.cpp
// Author      : Ragimov Islam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void UpdateIfGreater(int a, int& b)
{
	if (a > b){
		b = a;
	}
}

int main() {
	int a = 4;
	int b = 2;

	UpdateIfGreater(a, b);

	cout << b;
}
