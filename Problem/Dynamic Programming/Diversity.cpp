//https://atcoder.jp/contests/abc383/tasks/abc383_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const int M = 50005;

tuple<int, int, int> a[N];

long long dp[N][M][2];

int main() {
    IOS;
    int n, x, k;
    cin >> n >> x >> k;
    for (int i = 0; i < n; i++) {
        int p, u, c;
        cin >> p >> u >> c;
        a[i] = make_tuple(c, p, u);
    }
    sort(a, a + n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= x; j++) {
            dp[i][j][0] = -1;
            dp[i][j][1] = -1;
        }
    }
    auto [c, p, u] = a[0];
    dp[0][0][0] = 0;
    dp[0][p][1] = u + k;
    int last = c;
    for (int i = 1; i < n; i++) {
        auto [c, p, u] = a[i];
        for (int j = 0; j <= x; j++) {
            if (last == c) {
                if (dp[i - 1][j][0] != -1) {
                    dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][0]);
                    if (j + p <= x) dp[i][j + p][1] = max(dp[i][j + p][1], dp[i - 1][j][0] + u + k);
                }
                if (dp[i - 1][j][1] != -1) {
                    dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j][1]);
                    if (j + p <= x) dp[i][j + p][1] = max(dp[i][j + p][1], dp[i - 1][j][1] + u);
                }
            } else {
                if (dp[i - 1][j][0] != -1) {
                    dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][0]);
                    if (j + p <= x) dp[i][j + p][1] = max(dp[i][j + p][1], dp[i - 1][j][0] + u + k);
                }
                if (dp[i - 1][j][1] != -1) {
                    dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][1]);
                    if (j + p <= x) dp[i][j + p][1] = max(dp[i][j + p][1], dp[i - 1][j][1] + u + k);
                }
            }
        }
        last = c;
    }
    long long ans = 0;
    for (int j = 0; j <= x; j++) {
        ans = max({ans, dp[n - 1][j][0], dp[n - 1][j][1]});
    }
    cout << ans;
    return 0;
}
