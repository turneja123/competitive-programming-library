//https://cses.fi/problemset/task/1642/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

pair<int, int> a[N];
map<int, pair<int, int>> mp;

int main() {
    IOS;
    int n, x;
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a, a + n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            mp[a[i].first + a[j].first] = make_pair(i, j);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int need = x - (a[i].first + a[j].first);
            auto it = mp.find(need);
            if (it != mp.end() && j < it->second.first) {
                cout << a[i].second + 1 << " " << a[j].second + 1 << " " << a[it->second.first].second + 1 << " " << a[it->second.second].second + 1;
                return 0;
            }
        }
    }
    cout << "IMPOSSIBLE";

    return 0;
}
