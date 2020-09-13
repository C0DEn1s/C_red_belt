#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>

using namespace std;

class ReadingManager {
public:
    ReadingManager() : users_pages(), rating(1000, 0) {}
    void Read(int user_id, int page_count) {
        int prev_page;
        if (users_pages.size() != 0) {

            if (users_pages.count(user_id) == 1) {
                prev_page = users_pages[user_id];
            } else {
                prev_page = 0;
                users_pages.insert({user_id, page_count});
            }
            users_pages[user_id] = page_count;
        } else {
            prev_page = 0;
            users_pages.insert({user_id, page_count});
        }
        for (int i = prev_page; i < page_count; ++i) {
            rating[i]++;
        }
    }

    double Cheer(int user_id) const {
        if (users_pages.size() == 0) {
            return 0;
        }
        if (users_pages.count(user_id) == 0) {
            return 0;
        }
        if (users_pages.size() == 1) {
            return 1;
        }

        double result;
        result = (users_pages.size() - rating[users_pages.at(user_id) - 1]) * 1.0 / (users_pages.size() - 1);
        return result;
    }

private:
    map<int, int> users_pages;
    vector<int> rating;
};


int main2() {
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