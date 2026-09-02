//https://atcoder.jp/contests/abc468/tasks/abc468_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const ll M = 998244353;

ll dp[N][N];


int main() {
    IOS;
    int n;
    cin >> n;
    string s;
    cin >> s;
    if (s[0] == 'x') {
        cout << 0;
        return 0;
    }
    dp[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            dp[i][j] = (dp[i][j] + dp[i - 1][j] * 2 * j) % M;
            dp[i][j - 1] = (dp[i][j - 1] + dp[i - 1][j] * (j - 1)) % M;
            dp[i][j + 1] = (dp[i][j + 1] + dp[i - 1][j] * (j + 1)) % M;
        }
        if (s[i - 1] == 'x') {
            dp[i][1] = 0;
        } else {
            for (int j = 2; j <= i; j++) {
                dp[i][j] = 0;
            }
        }
    }
    cout << dp[n][1];
    return 0;
}
