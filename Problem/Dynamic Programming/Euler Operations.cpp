//https://www.codechef.com/START221A/problems/LMP9
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    vector<int> p{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    int t;
    cin >> t;
    while (t--) {
        int m, d;
        cin >> m >> d;
        vector<pair<int, int>> items{{1, 1}};
        for (int i : p) {
            pair<ll, ll> nx = {(ll)items.back().first * i, (ll)items.back().second * (i - 1)};
            if (nx.first <= m) {
                items.push_back(nx);
            }
        }
        reverse(items.begin(), items.end());

        map<int, int> dp;
        dp[0] = 0;
        for (auto [x, c] : items) {
            map<int, int> dp_nx = dp;
            for (auto [n, j] : dp) {
                int need = max(0, (d - n) / x);
                if (need > 0) {
                    auto it = dp_nx.find(n + need * x);
                    if (it == dp_nx.end()) {
                        dp_nx[n + need * x] = j + need * c;
                    } else {
                        dp_nx[n + need * x] = min(dp_nx[n + need * x], j + need * c);
                    }
                }
                auto it = dp_nx.find(2 * d - (n + (need + 1) * x));
                if (it == dp_nx.end()) {
                    dp_nx[2 * d - (n + (need + 1) * x)] = j + (need + 1) * c;
                } else {
                    dp_nx[2 * d - (n + (need + 1) * x)] = min(dp_nx[2 * d - (n + (need + 1) * x)], j + (need + 1) * c);
                }
            }
            dp = dp_nx;
        }
        cout << dp[d] << endl;
    }
    return 0;
}
