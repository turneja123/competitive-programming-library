//https://atcoder.jp/contests/abc307/tasks/abc307_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 998244353;

long long dp[2][N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    if (n == 2) {
        long long ans = (long long)m * (m - 1) % M;
        cout << ans;
        return 0;
    }
    dp[1][3] = (long long)m * (m - 1);
    dp[0][3] = (long long)m * (m - 1) % M * (m - 2) % M;
    for (int i = 4; i <= n; i++) {
        dp[0][i] = (dp[0][i - 1] * (m - 2) + dp[1][i - 1] * (m - 1)) % M;
        dp[1][i] = dp[0][i - 1];
    }
    cout << dp[0][n];

    return 0;
}
