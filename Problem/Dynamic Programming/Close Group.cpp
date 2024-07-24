//https://atcoder.jp/contests/abc187/tasks/abc187_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int K = 18;
const int N = 1 << K;

bool a[K][K];

int dp[N];

int main() {
    IOS;
    int k, m;
    cin >> k >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        a[u][v] = true;
        a[v][u] = true;

    }

    for (int j = 0; j < (1 << k); j++) {
        dp[j] = N;
        bool flag = true;
        for (int x = 0; x < k; x++) {
            for (int y = x + 1; y < k; y++) {
                int c1 = j & (1 << x), c2 = j & (1 << y);
                if (c1 > 0 && c2 > 0) {
                    if (!a[x][y]) {
                        flag = false;
                    }
                }
            }
        }
        if (flag) {
            dp[j] = 1;
        } else {
            for (int mask = j; mask > 0; mask = (mask - 1) & j) {
                dp[j] = min(dp[j], dp[mask] + dp[j ^ mask]);
            }
        }

    }
    cout << dp[(1 << k) - 1];
    return 0;
}
