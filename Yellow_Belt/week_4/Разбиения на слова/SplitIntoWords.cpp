#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<string> SplitIntoWords(const string& s){
	vector<string> answer;
	auto current_state = begin(s);
	
	for(auto char_it = begin(s); char_it != end(s); char_it++)
	{
		if (*char_it == *(find(char_it, end(s), ' ')) ) 
		{
            answer.push_back({current_state, char_it});
            current_state = ++char_it;
        }
    }
    answer.push_back({current_state, end(s)});
    
    return answer;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;
  
  return 0;
}
