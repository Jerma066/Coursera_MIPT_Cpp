#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
	const int MAX_ATHLETES = 100'000;
	using Position = list<int>::iterator;

	int n_athletes;
	cin >> n_athletes;

	list<int> row;
	vector<Position> athlete_pos(MAX_ATHLETES + 1, row.end());

	for (int i = 0; i < n_athletes; ++i) {
		int athlete, next_athlete;
		cin >> athlete >> next_athlete;
		/* Вставляем значение athlet в list, передавая ему итератор на 
		 * следующего по списку спортсмена */
		athlete_pos[athlete] = row.insert(athlete_pos[next_athlete], athlete);
		/* Метод insert возвращает итератор на вставляемое значение,
		 * его присваевоем элементу вектора, по индексу athlet */
	}

	for (int x : row) {
		cout << x << '\n';
	}
	
	return 0;
}
