//https://codeforces.com/contest/626/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 205;
const int K = 1005;
const ll M = 1e9 + 7;

int a[N];
int dp[N][N][K];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    dp[0][1][0] = 1;
    dp[0][0][0] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int d = 0; d <= k; d++) {
                int cost = d + j * (a[i] - a[i - 1]);
                if (cost > k) {
                    continue;
                }
                if (j != 0) {
                    dp[i][j - 1][cost] = (dp[i][j - 1][cost] + (ll)j * dp[i - 1][j][d]) % M;
                }
                dp[i][j][cost] = (dp[i][j][cost] + (ll)(j + 1) * dp[i - 1][j][d]) % M;
                dp[i][j + 1][cost] = (dp[i][j + 1][cost] + dp[i - 1][j][d]) % M;
            }
        }
    }
    int ans = 0;
    for (int d = 0; d <= k; d++) {
        ans = (ans + dp[n - 1][0][d]) % M;
    }
    cout << ans;

    return 0;
}
