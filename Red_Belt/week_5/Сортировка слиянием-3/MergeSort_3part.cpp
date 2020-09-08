#include <iostream>
#include <vector>
#include <algorithm>
#include "test_runner.h"

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
	int length = range_end - range_begin;
	if (length  < 2) {
        return;
    }

	vector<typename RandomIt::value_type> elems(std::make_move_iterator(range_begin), 
												std::make_move_iterator(range_end));
	vector<typename RandomIt::value_type> tmp;
	
	auto mid_1 = begin(elems) + length/3;
	auto mid_2 = mid_1 + length/3;
	
	MergeSort(begin(elems), mid_1);
	MergeSort(mid_1, mid_2);
	MergeSort(mid_2, end(elems));
	
	merge(make_move_iterator(begin(elems)), make_move_iterator(mid_1), 
		  make_move_iterator(mid_1), make_move_iterator(mid_2), 
		  back_inserter(tmp));
	
	merge(make_move_iterator(begin(tmp)), make_move_iterator(tmp.end()), 
		  make_move_iterator(mid_2), make_move_iterator(end(elems)), 
		  range_begin);
		  		  
}


void TestIntVector(){
    std::vector<int> numbers = { 6, 1, 3, 9, 1, 9, 8, 12, 1 };
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}

