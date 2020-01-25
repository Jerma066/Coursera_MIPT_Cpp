#include <iostream>
#include <string>
#include <deque>

using namespace std;

void AddBrackets (deque<string>& expression){
	expression.push_back(") ");
	expression.push_front("(");
}

void AddOperationWithNumber(deque<string>& expression, char operation, int number){
	AddBrackets(expression);
	expression.push_back(string(1, operation));
	expression.push_back(" ");
	expression.push_back(to_string(number));
}

int main() {
	int init_num, number_of_operations;
	deque<string> expression;

	cin >> init_num;
	expression.push_back(to_string(init_num));
	
	cin >> number_of_operations;
	
	for(int i = 0; i < number_of_operations; i++){
		char operation;
		int number;
		
		cin >> operation >> number;
		AddOperationWithNumber(expression, operation, number);
	}
	
	for (const string& s : expression) {
		cout << s;
	}
}
