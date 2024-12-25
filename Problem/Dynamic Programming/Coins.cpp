//https://atcoder.jp/contests/dp/tasks/dp_i
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

long double dp[N][N];
long double a[N];


int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    dp[0][0] = 1.0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] += ((long double)1.0 - a[i]) * dp[i - 1][j];
            dp[i][j + 1] += a[i] * dp[i - 1][j];
        }
    }
    long double ans = 0;
    for (int j = n / 2 + 1; j <= n; j++) {
        ans += dp[n][j];
    }
    cout << ans;
    return 0;
}
