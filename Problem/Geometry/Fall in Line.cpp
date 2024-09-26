//https://www.facebook.com/codingcompetitions/hacker-cup/2024/practice-round/problems/C/my-submissions
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());
pair<int, int> p[N];
map<tuple<int, int, long long>, set<int>> mp;


int main() {
    IOS;
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> p[i].first >> p[i].second;
        }
        for (int k = 0; k < max(10000, n); k++) {
            int i = generator() % n, j = generator() % n;
            if (i == j) {
                continue;
            }
            if (p[i].second > p[j].second) {
                swap(i, j);
            }
            long long a, b, c;
            if (p[i].first == p[j].first) {
                a = 1, b = 0, c = -p[i].first;
            } else {
                a = p[j].second - p[i].second, b = p[i].first - p[j].first;
                c = (long long)p[j].first * p[i].second - (long long)p[i].first * p[j].second;
            }
            long long g = __gcd(abs(c), __gcd(abs(a), abs(b)));
            a /= g, b /= g, c /= g;
            mp[make_tuple(a, b, c)].insert(i);
            mp[make_tuple(a, b, c)].insert(j);
        }
        int mx = 0; tuple<int, int, long long> line;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            if (mx < (int)(it->second).size()) {
                mx = (it->second).size();
                line = it->first;
            }
        }
        int ans = n;
        for (int i = 0; i < n; i++) {
            long long e = (long long)p[i].first * get<0>(line) + (long long)p[i].second * get<1>(line) + get<2>(line);
            if (e == 0) {
                ans--;
            }
        }
        cout << "Case #" << tt << ": " << ans << endl;
        mp.clear();
    }
    return 0;
}
