//https://atcoder.jp/contests/abc382/tasks/abc382_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 5005;

long double p[N];
long double dp[N][N];
long double ans[N];

int main() {
	IOS;
	cout << fixed;
	cout << setprecision(12);
	int n, x;
	cin >> n >> x;
	for (int i = 1; i <= n; i++) {
        cin >> p[i];
	}
	dp[0][0] = 1.0;
	for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= max(n, x); j++) {
            dp[i][j] = dp[i - 1][j] * ((long double)1.0 - p[i] / (long double)100.0);
            if (j != 0) {
                dp[i][j] += dp[i - 1][j - 1] * p[i] / (long double)100.0;
            }
        }
	}
	ans[0] = 0;
	for (int i = 1; i <= x; i++) {
        for (int j = 0; j <= i; j++) {
            ans[i] += dp[n][j] * ans[i - j];
        }
        ans[i] = (ans[i] + (long double)1.0) / ((long double)1.0 - dp[n][0]);
	}
	cout << ans[x];
	return 0;
}
