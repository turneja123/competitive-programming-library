//https://codeforces.com/contest/2109/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const long long M = 998244353;

long long dp[N][N];
long long cur[N][N][2];
int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                a[i + 1] = 0;
            } else {
                a[i + 1] = 1;
            }
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = 0;
                cur[i][j][0] = 0;
                cur[i][j][1] = 0;
            }
        }
        if (a[n] == 0) {
            dp[n][1] = 1;
            dp[n][0] = 1;
        } else {
            dp[n][0] = 1;
        }
        for (int i = n - 1; i > 0; i--) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = 0;
                for (int p = 0; j + p <= k; p++) {
                    cur[p][j][0] = 0;
                    cur[p][j][1] = 0;
                }
            }
            if (a[i] == 0) {
                cur[0][0][0] = 1;
                cur[0][1][1] = 1;
                dp[i][0] = 1;
                dp[i][1] = 1;
            } else {
                cur[0][0][1] = 1;
                dp[i][0] = 1;
            }
            for (int j = 1; j <= n; j++) {
                for (int p = 0; p <= k; p++) {
                    if (j + p > k) {
                        break;
                    }
                    cur[j][p][0] = (cur[j][p][0] + cur[j - 1][p][1]) % M;
                    cur[j][p][1] = (cur[j][p][1] + cur[j - 1][p][0]) % M;
                    if (p != 0) {
                        cur[j][p][1] = (cur[j][p][1] + cur[j - 1][p - 1][1]) % M;
                    }
                    dp[i][j + p] = (dp[i][j + p] + (cur[j][p][0] + cur[j][p][1]) * dp[i + 1][j]) % M;
                }
            }
        }
        cout << dp[1][k] << endl;
    }
    return 0;
}
