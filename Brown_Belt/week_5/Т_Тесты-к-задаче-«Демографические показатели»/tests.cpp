#include <sstream>

#include "test_runner.h"

void TestComputeMedianAgeWithEmpty() {
  vector<Person> persons;
  ASSERT_EQUAL(ComputeMedianAge(begin(persons), end(persons)), 0);
}

void TestComputeMedianAgeOffByOne() {
  vector<Person> persons = {Person{.age = 1}, Person{.age = 2}};
  ASSERT_EQUAL(ComputeMedianAge(begin(persons), end(persons)), 2);
  ASSERT_EQUAL(ComputeMedianAge(begin(persons), begin(persons) + 1), 1);
  ASSERT_EQUAL(ComputeMedianAge(begin(persons) + 1, begin(persons) + 2), 2);
}

void TestReadPersonsSwapFields() {
  stringstream stream;
  stream << 1 << endl
      << 25 << ' ' << 1 << ' ' << 0 << endl;

  ASSERT_EQUAL(
      ReadPersons(stream),
      vector<Person>({Person{.age = 25, .gender = Gender::MALE, .is_employed = false}})
  );
}

void TestReadPersonsInvertEmployed() {
  stringstream stream;
  stream << 1 << endl
      << 25 << ' ' << 1 << ' ' << 0 << endl;

  ASSERT_EQUAL(
      ReadPersons(stream),
      vector<Person>({Person{.age = 25, .gender = Gender::MALE, .is_employed = false}})
  );
}

void TestComputeStatsConfuseBounds() {
  const vector<Person> persons = {
      Person{.age = 32, .gender = Gender::MALE, .is_employed = true},
  };
  ASSERT_EQUAL(ComputeStats(persons).employed_males, 32);
}

void TestPrintStatsChangeOrder() {
  ostringstream stream;
  const AgeStats stats{
      .total = 40,
      .females = 78,
      .males = 40,
      .employed_females = 78,
      .unemployed_females = 80,
      .employed_males = 55,
      .unemployed_males = 40
  };
  PrintStats(stats, stream);
  ASSERT_EQUAL(
      stream.str(),
      "Median age = 40\n" \
      "Median age for females = 78\n" \
      "Median age for males = 40\n" \
      "Median age for employed females = 78\n" \
      "Median age for unemployed females = 80\n" \
      "Median age for employed males = 55\n" \
      "Median age for unemployed males = 40\n"
  );
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestComputeMedianAgeWithEmpty);
  RUN_TEST(tr, TestComputeMedianAgeOffByOne);
  RUN_TEST(tr, TestReadPersonsSwapFields);
  RUN_TEST(tr, TestReadPersonsInvertEmployed);
  RUN_TEST(tr, TestComputeStatsConfuseBounds);
  RUN_TEST(tr, TestPrintStatsChangeOrder);

  PrintStats(ComputeStats(ReadPersons()));
  return 0;
}
