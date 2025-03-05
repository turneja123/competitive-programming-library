//https://codeforces.com/contest/367/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int M = 1e9 + 7;

int main() {
    IOS;
    int n, m, x;
    cin >> n >> m >> x;
    if (n > m) {
        cout << 0;
        return 0;
    }
    vector<vector<vector<int>>> dp(m + 2, vector<vector<int>>(n + 2, vector<int>(n + 2)));
    dp[0][0][0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int k = 0; k <= n; k++) {
            for (int j = 0; j <= n; j++) {
                if (i != x) {
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j][k]) % M; //
                    if (j != 0) {
                        dp[i][j - 1][k] = (dp[i][j - 1][k] + dp[i - 1][j][k]) % M; //en
                    }
                }
                if (j != 0 && k != 0) {
                    dp[i][j][k + 1] = (dp[i][j][k + 1] + dp[i - 1][j][k]) % M; //st, en
                }
                dp[i][j + 1][k + 1] = (dp[i][j + 1][k + 1] + dp[i - 1][j][k]) % M; //st

            }
            dp[i][0][k + 1] = (dp[i][0][k + 1] + dp[i - 1][0][k]) % M;
        }
    }
    for (int i = 1; i <= n; i++) {
        dp[m][0][n] = (long long)dp[m][0][n] * i % M;
    }
    cout << dp[m][0][n];

    return 0;
}
