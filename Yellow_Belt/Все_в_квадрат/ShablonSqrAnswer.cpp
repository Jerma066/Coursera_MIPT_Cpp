#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <string>
using namespace std;



template<typename T> T Sqr (const T& value);
template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p);
template <typename T> vector<T> Sqr (const vector<T>& vi);
template <typename Key, typename Value> map<Key, Value> Sqr (const map<Key, Value>& m);


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
