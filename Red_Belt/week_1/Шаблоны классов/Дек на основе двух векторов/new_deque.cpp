#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class Deque{
public:
	Deque(){
	}
	
	bool Empty() const {
		return _front.empty() && _back.empty();
	}
	
	size_t Size() const {
		return _front.size() + _back.size();
	}
	
	T& operator[](size_t index) {
		if (index < _front.size()) { 
			return _front[_front.size() - 1 - index]; 
		} 
		return _back[index - _front.size()];
	}

	const T& operator[](size_t index) const {
		if (index < _front.size()) { 
			return _front[_front.size() - 1 - index]; 
		} 
		return _back[index - _front.size()];
	}
	
	T& At(const size_t& index) {
		if (index >= _front.size() + _back.size()) { 
			throw out_of_range("Index is out of range");
		}
		
		if (index < _front.size()) { 
			return _front[_front.size() - 1 - index]; 
		} 
		return _back[index - _front.size()];
	}

	const T& At(size_t index) const {
		if (index >= _front.size() + _back.size()) { 
			throw out_of_range("Index is out of range");
		}
		
		if (index < _front.size()) { 
			return _front[_front.size() - 1 - index]; 
		} 
		return _back[index - _front.size()];
	}
	
	T& Front() {
		return _front.empty() ? _back.front() : _front.back();
	}

	const T& Front() const {
		return _front.empty() ? _back.front() : _front.back();
	}

	T& Back() {
		return _back.empty() ? _front.front() : _back.back();
	}

	const T& Back() const {
		return _back.empty() ? _front.front() : _back.back();
	}
	
	void PushFront(const T& value) {
		_front.push_back(value);
	}

	void PushBack(const T& value) {
		_back.push_back(value);
	}
	
private:
	vector<T> _front;
	vector<T> _back;
};

int main(){
	Deque<int> test;
	test.PushFront(25);
	cout << test.Front() << endl;
	
	test.PushBack(11);
	cout << test.Back() << endl;
}
