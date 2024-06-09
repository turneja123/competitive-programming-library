//https://www.spoj.com/problems/REDRONESIA/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const long long M = 1e9 + 7;
const int N = 505;

long long dp[N][N][2];
long long pref[N][N];

long long calc(int n, int m) {
    for (int d = 0; d < m; d++) {
        dp[0][d][0] = 1;
        pref[0][d] = d + 1;
    }
    for (int i = 1; i < n; i++) {
        for (int d = 0; d < m; d++) {
            dp[i][d][1] = dp[i - 1][d][0];
            if (d != 0) {
                dp[i][d][0] = pref[i - 1][d - 1];
            } else {
                dp[i][d][0] = 0;
            }
        }
        for (int d = 0; d < m; d++) {
            pref[i][d] = (dp[i][d][0] + dp[i][d][1]) % M;
            if (d != 0) {
                pref[i][d] = (pref[i][d] + pref[i][d - 1]) % M;
            }
        }
    }
    long long ans = 0;
    for (int d = 0; d < m; d++) {
        ans = (ans + dp[n - 1][d][0] + dp[n - 1][d][1]) % M;
    }

    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        cout << calc(n, m) << endl;
    }

    return 0;
}
