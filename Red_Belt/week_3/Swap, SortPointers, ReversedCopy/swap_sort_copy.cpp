#include "test_runner.h"

#include <algorithm>
#include <numeric>

using namespace std;

template <typename T>
void Swap(T* first, T* second) {
	auto tmp = *first;
	*first = *second;
	*second = tmp;
}

template <typename T>
void SortPointers(vector<T*>& pointers) {
	sort(begin(pointers), end(pointers), [](T* lhs, T* rhs) {
		return *lhs < *rhs;
	});
}

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination) {
	auto source_begin = source;
	auto source_end = source + count;
	auto dest_begin = destination;
	auto dest_end = destination + count;
	if (dest_begin >= source_end || dest_end <= source_begin) {
		reverse_copy(source_begin, source_end, dest_begin);
	} 
	else if (dest_begin > source_begin) {
		/* Случай, когда целевая область лежит правее исходной
		 * |   |   |   |d_6|d_5|d_4|d_3|d_2|d_1|
		 * |s_1|s_2|s_3|s_4|s_5|s_6|   |   |   |
		 * */
		for (size_t i = 0; source_begin + i < dest_begin; ++i) {
		  *(dest_end - i - 1) = *(source_begin + i);
		}
		reverse(dest_begin, source_end);
	} 
	else {
		/* Случай, когда целевая область лежит левее исходной
		 * |d_6|d_5|d_4|d_3|d_2|d_1|   |   |   |
		 * |   |   |   |s_1|s_2|s_3|s_4|s_5|s_6|
		 * */
		for (size_t i = 0; source_end - i - 1 >= dest_end; ++i) {
		  *(dest_begin + i) = *(source_end - i - 1);
		}
		reverse(source_begin, dest_end);
	}
}

void TestSwap() {
  int a = 1;
  int b = 2;
  Swap(&a, &b);
  ASSERT_EQUAL(a, 2);
  ASSERT_EQUAL(b, 1);

  string h = "world";
  string w = "hello";
  Swap(&h, &w);
  ASSERT_EQUAL(h, "hello");
  ASSERT_EQUAL(w, "world");
}

void TestSortPointers() {
  int one = 1;
  int two = 2;
  int three = 3;

  vector<int*> pointers;
  pointers.push_back(&two);
  pointers.push_back(&three);
  pointers.push_back(&one);

  SortPointers(pointers);

  ASSERT_EQUAL(pointers.size(), 3u);
  ASSERT_EQUAL(*pointers[0], 1);
  ASSERT_EQUAL(*pointers[1], 2);
  ASSERT_EQUAL(*pointers[2], 3);
}

void TestReverseCopy() {
  const size_t count = 7;

  int* source = new int[count];
  int* dest = new int[count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  ReversedCopy(source, count, dest);
  const vector<int> expected1 = {7, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(dest, dest + count), expected1);

  // Области памяти могут перекрываться
  ReversedCopy(source, count - 1, source + 1);
  const vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(source, source + count), expected2);

  delete[] dest;
  delete[] source;
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSwap);
  RUN_TEST(tr, TestSortPointers);
  RUN_TEST(tr, TestReverseCopy);
  return 0;
}
