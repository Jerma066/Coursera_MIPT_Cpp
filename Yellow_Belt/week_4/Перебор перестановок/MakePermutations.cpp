#include <iostream>
#include <vector>

#include <algorithm>

using namespace std;

void PrintAllPermutations(int N){
	vector<int> permutation_vector(N);
	vector<int> output;
	
	for (int i = N; i > 0; --i) {
        permutation_vector[N-i] = i;
    }
    
    do{
		for (auto& it : permutation_vector) {
            std::cout << it << " ";
        }
        
        cout << endl;
	} while(next_permutation(begin(permutation_vector), end(permutation_vector), [](int lft, int rgh){return lft > rgh;}));
}

int main() {
    int N;
    cin >> N;
    PrintAllPermutations(N);
    return 0;
}
