//https://codeforces.com/contest/2075/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 60;
const int S = 120;

const long long INF = 3e18;
long long dp[K][S][S];


int main() {
    IOS;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < S; j++) {
            for (int k = 0; k < S; k++) {
                dp[i][j][k] = INF;
            }
        }
    }
    dp[0][0][0] = 0;
    for (int i = 1; i < K; i++) {
        long long cost = 1ll << i;
        for (int j = 0; j < S; j++) {
            for (int k = 0; k < S; k++) {
                if (dp[i - 1][j][k] == INF) {
                    continue;
                }
                dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k]);
                if (j + i < K) {
                    dp[i][j + i][k] = min(dp[i][j + i][k], dp[i - 1][j][k] + cost);
                }
                if (k + i < K) {
                    dp[i][j][k + i] = min(dp[i][j][k + i], dp[i - 1][j][k] + cost);
                }
            }
        }
    }

    int t;
    cin >> t;
    while (t--) {
        long long x, y;
        cin >> x >> y;
        string a = "", b = "";
        while (x > 0) {
            if (x % 2 == 0) {
                a += '0';
            } else {
                a += '1';
            }
            x /= 2;
        }
        while (y > 0) {
            if (y % 2 == 0) {
                b += '0';
            } else {
                b += '1';
            }
            y /= 2;
        }
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int n = a.size(), m = b.size();
        long long ans = dp[K - 1][n][m];
        for (int i = 0; i < min(n, m); i++) {
            string sa = a.substr(0, i + 1), sb = b.substr(0, i + 1);
            if (sa == sb) {
                ans = min(ans, dp[K - 1][n - i - 1][m - i - 1]);
            }
        }
        for (int i = 0; i + n < S; i++) {
            for (int j = 0; j + m < S; j++) {
                ans = min(ans, dp[K - 1][n + i][m + j]);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
