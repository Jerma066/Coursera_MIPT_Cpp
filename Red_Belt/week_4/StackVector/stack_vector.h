#pragma once

#include <array>
#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
	explicit StackVector(size_t a_size = 0) : size(a_size) {
		if (size > N) {
			throw invalid_argument("Too much");
		}
	}

	T& operator[](size_t index) {
		return data[index];
	}

	const T& operator[](size_t index) const {
		return data[index];
	}

	auto begin() {
		return data.begin();
	}

	auto end() {
		return data.begin() + size;
	}

	auto begin() const {
		return data.begin();
	}

	auto end() const {
		return data.begin() + size;
	}

	size_t Size() const {
		return size;
	}

	size_t Capacity() const {
		return N;
	}

	void PushBack(const T& value) {
		if (size >= N) {
			throw overflow_error("Full");
		} 
		else {
			data[size++] = value;
		}
	}

	T PopBack() {
		if (size == 0) {
			throw underflow_error("Empty");
		} 
		else {
			--size;
			return data[size];
		}
	}

private:
	array<T, N> data;
	size_t size = 0;
};
