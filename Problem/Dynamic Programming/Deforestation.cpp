//https://atcoder.jp/contests/abc209/tasks/abc209_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 4005;
const long long M = 1e9 + 7;

int a[N];
long long dp[N][N];
long long pref[N][N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    dp[0][0] = 1, pref[0][0] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (a[i - 1] < a[i]) {
                if (j != 0) {
                    dp[i][j] = pref[i - 1][j - 1];
                }
            } else if (a[i - 1] > a[i]) {
                if (j != i) {
                    dp[i][j] = (pref[i - 1][i - 1] - (j == 0 ? 0 : pref[i - 1][j - 1]) + M) % M;
                }
            } else {
                dp[i][j] = pref[i - 1][i - 1];
            }
            pref[i][j] = (j == 0 ? dp[i][j] : pref[i][j - 1] + dp[i][j]) % M;
        }
    }
    long long ans = 0;
    for (int j = 0; j < n; j++) {
        ans += dp[n - 1][j];
    }
    cout << ans % M;
    return 0;
}
