//https://ocpc2025s.eolymp.space/en/compete/m9rs3cu3vp6lv7kjgk9aaqsa1s/problem/6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<pair<int, int>> moves{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
set<pair<int, pair<int, int>>> heap;
map<pair<int, int>, int> mp;
set<pair<int, int>> points;

void add(int x, int y) {
    points.insert({x, y});
    for (auto [dx, dy] : moves) {
        auto it = mp.find({x + dx, y + dy});
        if (it == mp.end()) {
            mp[{x + dx, y + dy}] = 4;
        }
        mp[{x + dx, y + dy}]--;
        heap.insert(make_pair(mp[{x + dx, y + dy}], make_pair(x + dx, y + dy)));
    }
    return;
}


int main() {
    IOS;
    int n;
    cin >> n;
    cout << 2 * n + 6 << endl;
    add(0, 0);
    int x, y;
    cin >> x >> y;
    add(x, y);
    if (x + y > 0) {
        cout << "1 1" << endl;
        add(1, 1);
    } else {
        cout << "-1 -1" << endl;
        add(-1, -1);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        add(x, y);
        while (heap.size()) {
            auto [x, y] = heap.begin()->second;
            if (points.find({x, y}) != points.end()) {
                heap.erase(heap.begin());
            } else {
                cout << x << " " << y << endl;
                add(x, y);
                break;
            }
        }
    }

    return 0;
}
