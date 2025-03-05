//https://cses.fi/problemset/task/1665
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const int M = 10005;
const int MOD = 1e9 + 7;

int dp[N][N][M];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end(), greater<int>());
    dp[0][1][a[0]] = 1;
    dp[0][0][0] = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k < M; k++) {
                dp[i][j][k] = (dp[i][j][k] + (long long)(j + 1) * dp[i - 1][j][k]) % MOD;
                if (k + a[i] < M) {
                    dp[i][j + 1][k + a[i]] = (dp[i][j + 1][k + a[i]] + dp[i - 1][j][k]) % MOD;
                }
                if (j != 0 && k - a[i] >= 0) {
                    dp[i][j - 1][k - a[i]] = (dp[i][j - 1][k - a[i]] + (long long)j * dp[i - 1][j][k] % MOD) % MOD;
                }
            }
        }
    }
    long long ans = 0;
    for (int k = 0; k <= m; k++) {
        ans = (ans + dp[n - 1][0][k]) % MOD;
    }
    cout << ans;

    return 0;
}
