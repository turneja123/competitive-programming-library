//https://atcoder.jp/contests/dp/tasks/dp_t
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 3005;
const long long M = 1e9 + 7;

long long dp[N][N];
long long pref[N][N];

int main() {
    IOS;
    int n;
    cin >> n;
    string s;
    cin >> s;
    dp[0][0] = 1, pref[0][0] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (s[i - 1] == '<') {
                if (j != 0) {
                    dp[i][j] = pref[i - 1][j - 1];
                }
            } else {
                if (j != i) {
                    dp[i][j] = (pref[i - 1][i - 1] - (j == 0 ? 0 : pref[i - 1][j - 1]) + M) % M;
                }
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
