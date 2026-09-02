//https://qoj.ac/contest/636/problem/1647
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    map<pair<int, int>, vector<pair<int, int>>> mp;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    int a = (i - x + 3) % 3, b = (j - y + 3) % 3;
                    int ans = (a * (a - 1) / 2 + b * (b - 1) / 2 + 2 * a * b) % 3;
                    if (ans == 0) {
                        mp[{i, j}].push_back({x, y});
                    }
                }
            }
        }
    }
    map<pair<int, int>, int> ct;
    ct[{0, 0}]++;
    int n;
    cin >> n;
    int x = 0, y = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a % 3 == 1) {
            x = (x + 1) % 3;
        } else if (a % 3 == 2) {
            y = (y + 1) % 3;
        }
        for (auto [X, Y] : mp[{x, y}]) {
            ans += ct[{X, Y}];
        }
        ct[{x, y}]++;
    }
    cout << ans;

    return 0;
}
