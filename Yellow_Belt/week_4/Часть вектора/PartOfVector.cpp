#include <iostream>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int>& numbers){
	vector<int>::iterator vec_it;
	vector<int> number_copy = numbers;
	vector<int> reverse_answer;
	
	for(vec_it = number_copy.begin(); vec_it != number_copy.end(); vec_it++){
		if(*vec_it >= 0){
			reverse_answer.push_back(*vec_it);
		}
		else{
			break;
		}
	}
	
	for(vec_it = reverse_answer.end(); vec_it != reverse_answer.begin(); ){
		cout << *(--vec_it) << ' '; 
	}
}

int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
  return 0;
}
