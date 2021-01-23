#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

enum class Gender { FEMALE, MALE };

struct Person {
  int age;          // возраст
  Gender gender;    // пол
  bool is_employed; // имеет ли работу
};

// Подсчет не медианного возвраста, а среднего (написано для корректной сборки
// кода)
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  int sum = 0;
  int n = 0;
  for (auto it = range_begin; it != range_end; ++it) {
    sum += it->age;
    n++;
  }
  std::cout << "num: " << n << "\n";
  return sum / n;
}

void PrintStats(vector<Person> persons) {
  // Преобразуем порядок людей к следующему:
  //                  persons
  //                 /      \
    //          females        males
  //         /       \     /      \
    //      empl.  unempl. empl.   unempl.
  auto females_end =
      partition(begin(persons), end(persons),
                [](const Person &p) { return p.gender == Gender::FEMALE; });
  auto employed_females_end =
      partition(begin(persons), females_end,
                [](const Person &p) { return p.is_employed; });
  auto employed_males_end = partition(
      females_end, end(persons), [](const Person &p) { return p.is_employed; });

  // Теперь интересующие нас группы находятся в векторе непрерывно
  cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons))
       << endl;
  cout << "Median age for females = "
       << ComputeMedianAge(begin(persons), females_end) << endl;
  cout << "Median age for males = "
       << ComputeMedianAge(females_end, end(persons)) << endl;
  cout << "Median age for employed females = "
       << ComputeMedianAge(begin(persons), employed_females_end) << endl;
  cout << "Median age for unemployed females = "
       << ComputeMedianAge(employed_females_end, females_end) << endl;
  cout << "Median age for employed males = "
       << ComputeMedianAge(females_end, employed_males_end) << endl;
  cout << "Median age for unemployed males = "
       << ComputeMedianAge(employed_males_end, end(persons)) << endl;
}

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},   {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},    {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false}, {78, Gender::MALE, false},
      {10, Gender::FEMALE, false}, {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}
