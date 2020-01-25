#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
	int length = range_end - range_begin;
	
	if (length  < 2) {
        return;
    }
    else{
		vector<typename RandomIt::value_type> elems(range_begin, range_end);
		vector<typename RandomIt::value_type> tmp;
		
		auto mid_1 = begin(elems) + length/3;
		auto mid_2 = mid_1 + length/3;
		
		MergeSort(begin(elems), mid_1);
		MergeSort(mid_1, mid_2);
		MergeSort(mid_2, end(elems));
		
		merge(begin(elems), mid_1, mid_1, mid_2, back_inserter(tmp));
		merge(begin(tmp), tmp.end(), mid_2, end(elems), range_begin);
	}

}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
