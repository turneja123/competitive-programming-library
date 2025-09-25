//https://atcoder.jp/contests/arc206/tasks/arc206_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 998244353;

int a[N];
ll dp[N][3];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    if (n == 1) {
        cout << 1;
        return 0;
    }
    if (a[1] == -1) {
        dp[1][1] = 1;
        dp[1][2] = n - 1;
    } else {
        if (a[1] == 2) {
            dp[1][1] = 1;
        } else {
            dp[1][2] = 1;
        }
    }
    for (int i = 2; i <= n; i++) {
        if (a[i] == -1) {
            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % M;
            dp[i][1] = dp[i - 1][1] * (i == n ? 0 : 1);
            dp[i][2] = dp[i - 1][1] * (n - 1 - ((i == n) ? 0 : 1)) % M;
        } else {
            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) * (a[i] == i - 1) % M;
            dp[i][1] = dp[i - 1][1] * (a[i] == i + 1) % M;
            dp[i][2] = dp[i - 1][1] * (a[i] != i - 1 && a[i] != i + 1) % M;
        }
    }
    cout << (dp[n][0] + dp[n][1] + dp[n][2]) % M;

    return 0;
}
