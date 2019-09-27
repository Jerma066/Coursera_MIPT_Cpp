#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <string>
using namespace std;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~Выводы контейнеров~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <typename Collection>
string Join(const Collection& c, char d) {
  stringstream ss;
  bool first = true;
  for (const auto& i : c) {
    if (!first) {
      ss << d;
    }
    first = false;
    ss << i;
  }
  return ss.str();
}

template <typename First, typename Second>
ostream& operator << (ostream& out, const pair<First, Second>& p) {
  return out << '(' << p.first << ',' << p.second << ')';
}

template <typename T>
ostream& operator << (ostream& out, const vector<T>& vi) {
  return out << '[' << Join(vi, ',') << ']';
}

template <typename Key, typename Value>
ostream& operator << (ostream& out, const map<Key, Value>& m) {
  return out << '{' << Join(m, ',') << '}';
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~Возведение в квадрат~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template<typename T>
T Sqr (const T& value){
	T answer = value*value;
	return answer;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p) {
  pair<First, Second> answer = p;
  answer.first = Sqr(p.first);
  answer.second = Sqr(p.second);
  
  return answer;
}

template <typename T>
vector<T> Sqr (const vector<T>& vi) {
	vector<T> answer;
	
	for(auto i: vi){
		answer.push_back(Sqr(i));
	}
	
	return answer;
}

template <typename Key, typename Value>
map<Key, Value> Sqr (const map<Key, Value>& m) {
  	map<Key, Value> answer;
	for(const auto& it : m){
		answer[it.first] = Sqr(it.second);
	}
	
	return answer;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


int main() {
  vector<double> vi = {1.4, 2, 3};
  vector<double> answer = Sqr(vi);
  cout << answer << endl;
  map<int, double> m = {{1, 2.5}, {3, 4}};
  cout << Sqr(m) << endl;
  vector<vector<int>> v = {{1, 2}, {3, 4}};
  cout << Sqr(v) << endl;
  return 0;
}
