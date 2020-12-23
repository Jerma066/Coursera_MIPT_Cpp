#include "animals.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using Zoo = std::vector<std::unique_ptr<Animal>>;

Zoo CreateZoo(std::istream& in) {
  Zoo zoo;
  std::string word;
  while (in >> word) {
    if (word == "Tiger") {
      zoo.push_back(std::make_unique<Tiger>());
    } else if (word == "Wolf") {
      zoo.push_back(std::make_unique<Wolf>());
    } else if (word == "Fox") {
      zoo.push_back(std::make_unique<Fox>());
    } else {
      throw std::runtime_error("Unknown animal!");
    }
  }
  return zoo;
}

void Process(const Zoo& zoo, std::ostream& out) {
  for (const auto& animal : zoo) {
    out << animal->Voice() << "\n";
  }
}

void TestZoo() {

  std::istringstream input("Tiger Wolf Fox Tiger");
  std::ostringstream output;
  Process(CreateZoo(input), output);

  const std::string expected =
    "Rrrr\n"
    "Wooo\n"
    "Tyaf\n"
    "Rrrr\n";

  ASSERT_EQUAL(output.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestZoo);
}
