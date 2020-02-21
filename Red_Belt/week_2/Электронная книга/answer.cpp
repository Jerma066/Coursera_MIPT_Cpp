#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>

using namespace std;

class ReadingManager {
public:
	ReadingManager() = default;

    void Read(int user_id, int page_count) {        
        if (users_page_count.count(user_id) != 0) {
            int old_page_count = users_page_count[user_id];
            auto it = users_on_page[old_page_count].find(user_id);
            if (it != users_on_page[old_page_count].end()) {
                users_on_page[old_page_count].erase(it);
            }
        }
        users_page_count[user_id] = page_count;
        users_on_page[page_count].insert(user_id);
    }

    double Cheer(int user_id) const {
        if (users_page_count.count(user_id) == 0) {
            return 0;
        }
        auto user_count = users_page_count.size();
        if (user_count == 1) {
            return 1;
        }

        int count = 0;
        int current_user_page = users_page_count.at(user_id);
        for (auto i = 1; i < current_user_page; ++i) {
            count += users_on_page[i].size();
        }

        return count * 1.0 / (user_count - 1);
    }

private:
	// Статическое поле не принадлежит какому-то конкретному
	// объекту класса. По сути это глобальная переменная,
	// в данном случае константная.
	// Будь она публичной, к ней можно было бы обратиться снаружи
	// следующим образом: ReadingManager::MAX_USER_COUNT.
	static const int MAX_PAGE_COUNT = 1000;
	
	map<int, int> users_page_count;
    vector<set<int>> users_on_page{1001};
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
