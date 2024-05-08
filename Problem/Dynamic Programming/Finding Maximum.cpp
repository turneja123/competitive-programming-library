//https://www.spoj.com/problems/FINDMAX/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const long long M = 1e9 + 7;
const int N = 105;
const int K = 305;

long long dp[N][N][K];
long long pref[N][N][K];

int main() {
    IOS;
    for (int k = 1; k < K; k++) {
        dp[0][0][k] = 1;
        pref[0][0][k] = k;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 1; k < K; k++) {
                dp[i][j][k] = (dp[i][j][k] + (long long)k * dp[i - 1][j][k]) % M;
                if (j > 0 && k > 1) {
                    dp[i][j][k] = (dp[i][j][k] + pref[i - 1][j - 1][k - 1]) % M;
                }
                pref[i][j][k] = (pref[i][j][k - 1] + dp[i][j][k]) % M;
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, k, p;
        cin >> n >> k >> p;
        long long ans = 0;
        for (int i = 1; i <= k; i++) {
            ans = (ans + dp[n - 1][p][i]) % M;
        }
        cout << ans << endl;
    }
    return 0;
}
