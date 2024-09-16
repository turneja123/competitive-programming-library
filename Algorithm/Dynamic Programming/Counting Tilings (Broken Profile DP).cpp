//https://cses.fi/problemset/task/2181/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 10;
const int M = 1000;
const long long MOD = 1e9 + 7;

long long dp[N][M][1 << N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    dp[0][0][(1 << n) - 2] = 1;
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            if (i == 0 && j == 0) {
                continue;
            }
            for (int mask = 0; mask < 1 << n; mask++) {
                if (i == 0) {
                    dp[i][j][mask] = dp[n - 1][j - 1][mask ^ (1 << i)];
                } else {
                    dp[i][j][mask] = dp[i - 1][j][mask ^ (1 << i)];
                    if ((mask & (1 << i)) && (mask & (1 << i - 1))) {
                        dp[i][j][mask] += dp[i - 1][j][mask ^ (1 << i - 1)];
                    }
                }
                dp[i][j][mask] %= MOD;
            }
        }
    }
    cout << dp[n - 1][m - 1][(1 << n) - 1];

    return 0;
}
