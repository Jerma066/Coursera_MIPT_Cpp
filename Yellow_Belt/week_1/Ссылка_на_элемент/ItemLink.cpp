#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <string>

using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict (map<Key, Value>& m, const Key& key){
	
	if(m.count(key) == 0){
		throw runtime_error("exception!");
	}
	
	Value& answer = m[key]; 
	return answer;
}

int main(){
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue
}
