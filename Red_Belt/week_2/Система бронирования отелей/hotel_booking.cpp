#include <iostream>
#include <queue>
#include <string>
#include <map>

using namespace std;

struct Info_card {
    int64_t time;
    string hotel_name;
    uint64_t client_id;
    uint16_t room_count;
};

class HotelReservationSystem {
public:
    void Book(int64_t time, const string &hotel_name, uint64_t client_id, uint16_t room_count) {
        current_time = time;
        time_line.push({time, hotel_name, client_id, room_count});
        book_client_id[hotel_name][client_id] += room_count;
        book_room_count[hotel_name] += room_count;
    }

    uint64_t Clients(const string &hotel_name) {
        if (book_client_id.count(hotel_name) == 0) { return 0; }

        Adjust(hotel_name);
        return book_client_id[hotel_name].size();
    }

    uint64_t Rooms(const string &hotel_name) {
        if (book_room_count.count(hotel_name) == 0) { return 0; }

        Adjust(hotel_name);
        return book_room_count[hotel_name];
    }

private:
    queue<Info_card> time_line;
    map<string, map<uint64_t, uint64_t>> book_client_id;
    map<string, uint64_t> book_room_count;
    int64_t current_time = 0;

    void Adjust(const string &hotel_name) {
        while (!time_line.empty() && time_line.front().time <= current_time - 86400) {
            auto &hn = time_line.front().hotel_name;
            auto &rc = time_line.front().room_count;
            auto cid = time_line.front().client_id;
            book_room_count[hn] -= rc;
            if (book_room_count[hn] == 0) book_room_count.erase(hn);
            book_client_id[hn][cid] -= rc;
            if (book_client_id[hn][cid] == 0) book_client_id[hn].erase(cid);
            time_line.pop();
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    HotelReservationSystem hrs;

    int q;
    cin >> q;

	for (auto i = 0; i < q; ++i) {
		string operation;
		cin >> operation;

		if (operation == "BOOK") {
			uint64_t time;
			string hotel_name;
			uint64_t client_id;
			uint16_t room_count;
			cin >> time >> hotel_name >> client_id >> room_count;
			hrs.Book(time, hotel_name, client_id, room_count);
		} else if (operation == "CLIENTS") {
			string hotel_name;
			cin >> hotel_name;
			auto count = hrs.Clients(hotel_name);
			cout << count << '\n';
		} else if (operation == "ROOMS") {
			string hotel_name;
			cin >> hotel_name;
			auto count = hrs.Rooms(hotel_name);
			cout << count << '\n';
	  }
	}


    return 0;
}
