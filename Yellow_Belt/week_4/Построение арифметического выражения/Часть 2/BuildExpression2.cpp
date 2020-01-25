#include <iostream>
#include <string>
#include <deque>

using namespace std;

void AddBrackets (deque<string>& expression){
	expression.push_back(")");
	expression.push_front("(");
}

void AddOperationWithNumber(deque<string>& expression, char prev_operation, char cur_operation, int number){
	if((prev_operation == '+' || prev_operation == '-') && (cur_operation == '*' || cur_operation == '/')){
		AddBrackets(expression);
	}
	expression.push_back(" ");
	expression.push_back(string(1, cur_operation));
	expression.push_back(" ");
	expression.push_back(to_string(number));
}

int main() {
	int init_num, number_of_operations;
	deque<string> expression;

	cin >> init_num;
	expression.push_back(to_string(init_num));
	
	cin >> number_of_operations;
	
	char prev_operation;
	for(int i = 0; i < number_of_operations; i++){
		char cur_operation;
		int number;
		
		cin >> cur_operation >> number;
		AddOperationWithNumber(expression, prev_operation, cur_operation, number);
		prev_operation = cur_operation;
	}
	
	for (const string& s : expression) {
		cout << s;
	}
}
