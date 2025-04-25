//https://dmoj.ca/problem/ceoi16p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const long long M = 1e9 + 7;

long long dp[N][N];

int main() {
    IOS;
    int n, l, r;
    cin >> n >> l >> r;
    dp[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (i == l || i == r) {
                dp[i][j + 1] = (dp[i][j + 1] + dp[i - 1][j]) % M;
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % M;
            } else {
                dp[i][j + 1] = (dp[i][j + 1] + dp[i - 1][j] * (j - 1)) % M;
                if (i < l) {
                    dp[i][j + 1] = (dp[i][j + 1] + dp[i - 1][j]) % M;
                }
                if (i < r) {
                    dp[i][j + 1] = (dp[i][j + 1] + dp[i - 1][j]) % M;
                }
                dp[i][j - 1] = (dp[i][j - 1] + dp[i - 1][j] * (j - 1)) % M;
            }
        }
    }
    cout << dp[n][1];
    return 0;
}
