#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <numeric>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

private:
  Iterator first, last;
};

struct Person {
  string name;
  int age, income;
  bool is_male;
};

vector<Person> ReadPeople(istream& input) {
  int count;
  input >> count;

  vector<Person> result(count);
  for (Person& p : result) {
    char gender;
    input >> p.name >> p.age >> p.income >> gender;
    p.is_male = gender == 'M';
  }

  return result;
}

template <typename Iter>
std::optional<string> FindMostPopularName(IteratorRange<Iter> range) {
  if (range.begin() == range.end()) {
    return std::nullopt;
  } else {
    sort(range.begin(), range.end(), [](const Person& lhs, const Person& rhs) {
      return lhs.name < rhs.name;
    });
    const string* most_popular_name = &range.begin()->name;
    int count = 1;
    for (auto i = range.begin(); i != range.end(); ) {
      auto same_name_end = find_if_not(i, range.end(), [i](const Person& p) {
        return p.name == i->name;
      });
      const auto cur_name_count = std::distance(i, same_name_end);
      if (
        cur_name_count > count ||
        (cur_name_count == count && i->name < *most_popular_name)
      ) {
        count = cur_name_count;
        most_popular_name = &i->name;
      }
      i = same_name_end;
    }
    return *most_popular_name;
  }
}

struct StatsData {
  std::optional<string> most_popular_male_name;
  std::optional<string> most_popular_female_name;
  vector<int> cumulative_wealth;
  vector<Person> sorted_by_age;
};

StatsData BuildStatsData(vector<Person> people) {
  StatsData result;

  {
    IteratorRange males{
      begin(people),
      partition(begin(people), end(people), [](const Person& p) {
        return p.is_male;
      })
    };
    IteratorRange females{males.end(), end(people)};

    // По мере обработки запросов список людей не меняется, так что мы можем
    // один раз найти самые популярные женское и мужское имена
    result.most_popular_male_name = FindMostPopularName(males);
    result.most_popular_female_name = FindMostPopularName(females);
  }

  // Запросы WEALTHY можно тоже обрабатывать за О(1), один раз отсортировав всех
  // людей по достатку и посчитав массив префиксных сумм
  {
    sort(people.begin(), people.end(), [](const Person& lhs, const Person& rhs) {
      return lhs.income > rhs.income;
    });

    auto& wealth = result.cumulative_wealth;
    wealth.resize(people.size());
    if (!people.empty()) {
      wealth[0] = people[0].income;
      for (size_t i = 1; i < people.size(); ++i) {
        wealth[i] = wealth[i - 1] + people[i].income;
      }
    }
  }

  sort(begin(people), end(people), [](const Person& lhs, const Person& rhs) {
    return lhs.age < rhs.age;
  });
  result.sorted_by_age = std::move(people);

  return result;
}

int main() {
  // Основной проблемой исходного решения было то, что в нём случайно изменялись
  // входные данные. Чтобы ганатировать, что этого не произойдёт, мы организовываем код
  // так, чтобы в месте обработки запросов были видны только константные данные.
  //
  // Для этого всю их предобработку мы вынесли в отдельную функцию, результат которой
  // сохраняем в константной переменной.
  const StatsData stats = BuildStatsData(ReadPeople(cin));

  for (string command; cin >> command; ) {
    if (command == "AGE") {
      int adult_age;
      cin >> adult_age;

      auto adult_begin = lower_bound(
        begin(stats.sorted_by_age),
        end(stats.sorted_by_age),
        adult_age,
        [](const Person& lhs, int age) {
          return lhs.age < age;
        }
      );

      cout << "There are " << std::distance(adult_begin, end(stats.sorted_by_age))
           << " adult people for maturity age " << adult_age << '\n';
    } else if (command == "WEALTHY") {
      int count;
      cin >> count;
      cout << "Top-" << count << " people have total income "
           << stats.cumulative_wealth[count - 1] << '\n';
    } else if (command == "POPULAR_NAME") {
      char gender;
      cin >>gender;
      const auto& most_popular_name = gender == 'M' ? stats.most_popular_male_name
                                                    : stats.most_popular_female_name;
      if (most_popular_name) {
        cout << "Most popular name among people of gender " << gender << " is "
             << *most_popular_name << '\n';
      } else {
        cout << "No people of gender " << gender << '\n';
      }
    }
  }
}
