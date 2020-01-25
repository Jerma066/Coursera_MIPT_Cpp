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
		
		auto mid = begin(elems) + length/2;
		
		MergeSort(begin(elems), mid);
		MergeSort(mid, end(elems));
		
		merge(begin(elems), mid, mid, end(elems), range_begin);
	}

}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
