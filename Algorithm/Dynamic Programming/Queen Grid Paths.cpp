//solution for https://atcoder.jp/contests/abc183/tasks/abc183_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const ll M = 1e9 + 7;

ll dp[N][N];
ll x[N][N];
ll y[N][N];
ll z[N][N];
char c[N][N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> c[i][j];
            dp[i][j] = 0;
            x[i][j] = 0;
            y[i][j] = 0;
            z[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (c[i][j] == '.') {
                if (i > 0) {
                    y[i][j] = y[i - 1][j] + dp[i - 1][j];
                    y[i][j] %= M;
                    dp[i][j] += y[i][j];
                }
                if (j > 0) {
                    x[i][j] = x[i][j - 1] + dp[i][j - 1];
                    x[i][j] %= M;
                    dp[i][j] += x[i][j];
                }
                if (i > 0 && j > 0) {
                    z[i][j] = z[i - 1][j - 1] + dp[i - 1][j - 1];
                    z[i][j] %= M;
                    dp[i][j] += z[i][j];
                }
                dp[i][j] %= M;
            }
        }
    }
    cout << dp[n - 1][m - 1] << endl;
    return 0;
}

