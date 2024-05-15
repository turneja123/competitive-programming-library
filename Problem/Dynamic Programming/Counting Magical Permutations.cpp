//https://www.spoj.com/problems/BDOI16C/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const int M = 10007;

int dp[N][N];
int f[N];

int main() {
    IOS;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = -1;
        }
        f[i] = ((i == 0) ? 1 : f[i - 1] * i % M);
    }
    dp[1][0] = 1;
    for (int i = 2; i < N; i++) {
        dp[i][0] = 1;
        for (int j = 1; j < N; j++) {
            if (dp[i][j - 1] != -1) {
                dp[i][j] = dp[i][j - 1] + max(0, dp[i - 1][j]) - ((j - i) >= 0 ? max(0, dp[i - 1][j - i]) : 0);
                dp[i][j] = (dp[i][j] + M) % M;
            }
        }
    }
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n, k;
        cin >> n >> k;
        int ans = f[n];
        for (int j = 0; j < k; j++) {
            if (dp[n][j] != -1) {
                ans = (ans - dp[n][j] + M) % M;
            }
        }
        cout << "Case " << tt << ": " << ans << endl;
    }


    return 0;
}
