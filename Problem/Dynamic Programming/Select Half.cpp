//https://atcoder.jp/contests/abc162/tasks/abc162_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int mid = 5;
const long long INF = 1e18;

long long a[N];
long long dp[N][11][2];

int main() {
	IOS;
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
        cin >> a[i];
        for (int j = 0; j < 11; j++) {
            dp[i][j][0] = -INF;
            dp[i][j][1] = -INF;
        }
	}
	dp[1][mid][0] = 0;
	dp[1][mid + 1][1] = a[1];
	for (int i = 2; i <= n; i++) {
        int diff = i / 2 - (i - 1) / 2;
        for (int j = 0; j < 11; j++) {
            if (j + diff < 11) {
                dp[i][j][0] = max(dp[i - 1][j + diff][0], dp[i - 1][j + diff][1]);
            }
            if (j + diff - 1 >= 0) {
                dp[i][j][1] = dp[i - 1][j + diff - 1][0] + a[i];
            }
        }
	}
	cout << max(dp[n][mid][0], dp[n][mid][1]);
	return 0;
}
