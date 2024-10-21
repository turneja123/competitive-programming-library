//https://codeforces.com/contest/2025/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const long long M = 998244353;

int ones[N][N];
int others[N][N][N];
int dp[N][N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    ones[1][1] = 1;
    for (int i = 2; i <= m; i++) {
        for (int j = 0; j <= i; j++) {
            if (i != 0) {
                ones[i][j] += ones[i - 1][j - 1];
            }
            if (i != j) {
                ones[i][j] += ones[i - 1][j + 1];
            }
            ones[i][j] %= M;
        }
    }
    others[1][1][0] = 1, others[1][0][1] = 1;
    for (int i = 2; i <= m; i++) {
        for (int j = 0; j <= i - 1; j++) {
            for (int k = 0; k <= i - 1; k++) {
                if (k == 0) {
                    others[i][j + 1][k] = (others[i][j + 1][k] + others[i - 1][j][k]) % M;
                } else {
                    others[i][j][k - 1] = (others[i][j][k - 1] + others[i - 1][j][k]) % M;
                }
                others[i][j][k + 1] = (others[i][j][k + 1] + others[i - 1][j][k]) % M;
            }
        }

    }
    for (int j = 0; j <= m; j++) {
        dp[1][j] = ones[m][j];
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= j; k++) {
                dp[i][j - k] = ((long long)dp[i][j - k] + (long long)dp[i - 1][j] * others[m][k][0]) % M;
            }
        }
    }
    cout << dp[n][0];
    return 0;
}
