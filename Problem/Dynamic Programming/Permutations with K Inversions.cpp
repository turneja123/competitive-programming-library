//https://www.spoj.com/problems/PERMUT1/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 25, K = 100;

int dp[N][K];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = -1;
            }
        }
        dp[1][0] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i][0] = 1;
            for (int j = 1; j <= k; j++) {
                if (dp[i][j - 1] != -1) {
                    dp[i][j] = dp[i][j - 1] + max(0, dp[i - 1][j]) - ((j - i) >= 0 ? max(0, dp[i - 1][j - i]) : 0);
                }
                /*for (int p = j; p >= 0 && j - p < i; p--) {
                    if (dp[i - 1][p] != -1) {
                        if (dp[i][j] == -1) {
                            dp[i][j] = dp[i - 1][p];
                        } else {
                            dp[i][j] = dp[i][j] + dp[i - 1][p];
                        }
                    }
                }*/
            }
        }
        cout << ((dp[n][k] == -1) ? 0 : dp[n][k]) << endl;

    }
    return 0;
}
