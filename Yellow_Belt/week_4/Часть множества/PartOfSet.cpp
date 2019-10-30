#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border){
	typename set<T>::iterator set_it;
	set<T> copy_elements = elements;
	vector<T> answer;
	
	for(set_it = copy_elements.begin(); set_it != copy_elements.end(); set_it++){
		if(*set_it > border){
			answer.push_back(*set_it);
		}
	}
	
	return answer;
}

int main() {
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
    cout << x << " ";
  }
  cout << endl;
  
  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
  return 0;
}
