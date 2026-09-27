//bbc15
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll MAX = 1e14;
const int N = 15;
const int S = 14 * 9 + 1;

ll dp[N][S][S][3];

ll calc(ll n, int m) {
    ll ans = 0;
    if (n == MAX) {
        ans += m == 1;
        n--;
    }
    vector<int> d;
    while (n > 0) {
        d.push_back(n % 10);
        n /= 10;
    }
    reverse(d.begin(), d.end());
    dp[0][0][0][2] = 1;
    n = d.size();
    for (int i = 1; i <= n; i++) {
        int c = d[i - 1];
        for (int s = 0; s <= min(m, 9 * (i - 1)); s++) {
            for (int k = 0; k < m; k++) {
                for (int add = 0; add < 10 && s + add <= m; add++) {
                    if (i == 1 && add == 0) {
                        continue;
                    }
                    for (int t = 0; t < 3; t++) {
                        int t_nx = t;
                        if (t == 2 && add < c) {
                            t_nx = 0;
                        }
                        if (t == 2 && add > c) {
                            t_nx = 1;
                        }
                        dp[i][s + add][(k * 10 + add) % m][t_nx] += dp[i - 1][s][k][t];
                    }
                }
            }
        }
        ans += dp[i][m][0][0] + dp[i][m][0][2];
        if (i != n) {
            ans += dp[i][m][0][1];
        }
    }
    for (int i = 0; i <= n; i++) {
        for (int s = 0; s <= min(m, 9 * i); s++) {
            for (int k = 0; k < m; k++) {
                for (int t = 0; t < 3; t++) {
                    dp[i][s][k][t] = 0;
                }
            }
        }
    }
    return ans;
}


int main() {
    IOS;
    ll l, r;
    cin >> l >> r;
    ll ans = 0;
    for (int i = 1; i < S; i++) {
        ans += calc(r, i) - calc(l - 1, i);
    }
    cout << ans;

    return 0;
}
