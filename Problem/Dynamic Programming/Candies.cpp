//https://atcoder.jp/contests/dp/tasks/dp_m
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const int K = 1e5 + 5;
const long long M = 1e9 + 7;

int a[N];
long long dp[N][K];
long long pref[K];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int j = 0; j <= a[0]; j++) {
        dp[0][j] = 1;
    }
    for (int j = 0; j <= m; j++) {
        pref[j] = dp[0][j] + ((j == 0) ? 0 : pref[j - 1]);
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            int l = max(0, j - a[i]);
            dp[i][j] = pref[j];
            if (l > 0) {
                dp[i][j] = (dp[i][j] - pref[l - 1] + M) % M;
            }
        }
        for (int j = 0; j <= m; j++) {
            pref[j] = (dp[i][j] + ((j == 0) ? 0 : pref[j - 1])) % M;
        }
    }
    cout << dp[n - 1][m];
    return 0;
}
