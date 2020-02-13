#include <iostream>
#include <utility>
#include <vector>

#include "test_runner.h"

using namespace std;

template <typename T>
class Table {
public:
	Table(size_t rows, size_t columns):
		numOfRows(rows),
		numOfCols(columns)
	{
		Resize(rows, columns);
	}
	
	pair<size_t, size_t> Size() const{
		return pair<size_t, size_t>(numOfRows, numOfCols);
	}
	
	const vector<T>& operator [] (size_t idx) const {
		return data[idx];
	}

	vector<T>& operator [] (size_t idx) {
		return data[idx];
	}
	
	void Resize(size_t rows, size_t columns) {
		data.resize(rows);
		for (auto& item : data) {
			item.resize(columns);
		}
		
		numOfRows = rows;
		numOfCols = columns;
	}
	
private:
	size_t numOfRows;
	size_t numOfCols;
	vector< vector<T> > data;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
