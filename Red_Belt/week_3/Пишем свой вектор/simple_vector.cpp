#include "simple_vector.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Реализация класса
template <typename T>
SimpleVector<T>::SimpleVector():
	_size(0),
	_capacity(0),
	_data(nullptr),
	_end(nullptr)
{
}

template <typename T>
SimpleVector<T>::SimpleVector(size_t size):
	_size(size),
	_capacity(size)
{
	_data = new T[size];
	_end = _data + size;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index) {
	return _data[index];
}

template <typename T>
SimpleVector<T>::~SimpleVector() {
	delete[] _data;
}

template <typename T>
T* SimpleVector<T>::begin() {
  return _data;
}

template <typename T>
T* SimpleVector<T>::end() {
  return _end;
}

template <typename T>
const T* SimpleVector<T>::begin() const {
  return _data;
}

template <typename T>
const T* SimpleVector<T>::end() const {
  return _end;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const {
	return _capacity;
}

template <typename T>
size_t SimpleVector<T>::Size() const {
	return _size;
}

template <typename T>
void SimpleVector<T>::PushBack(const T& value) {
	if (Size() == 0) {
		_capacity++;
		_data = new T[_capacity];
	}
	else if (Size() == Capacity()) {
		T* old_data = _data;
		_capacity *= 2;
		_data = new T[_capacity];

		for (size_t i = 0; i < Size(); ++i) {
			_data[i] = old_data[i];
		}

		delete[] old_data;
	}

	_data[_size] = value;
	_size++;
	_end = _data + _size;
}

// Тестирование
void TestConstruction() {
  SimpleVector<int> empty;
  ASSERT_EQUAL(empty.Size(), 0u);
  ASSERT_EQUAL(empty.Capacity(), 0u);
  ASSERT(empty.begin() == empty.end());

  SimpleVector<string> five_strings(5);
  ASSERT_EQUAL(five_strings.Size(), 5u);
  ASSERT(five_strings.Size() <= five_strings.Capacity());
  for (auto& item : five_strings) {
    ASSERT(item.empty());
  }
  five_strings[2] = "Hello";
  ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
  SimpleVector<int> v;
  for (int i = 10; i >= 1; --i) {
    v.PushBack(i);
    ASSERT(v.Size() <= v.Capacity());
  }
  sort(begin(v), end(v));

  const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQUAL(v.Size(), expected.size());
  ASSERT(equal(begin(v), end(v), begin(expected)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConstruction);
  RUN_TEST(tr, TestPushBack);
  return 0;
}
