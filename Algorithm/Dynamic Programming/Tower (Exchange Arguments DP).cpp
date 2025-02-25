//https://atcoder.jp/contests/dp/tasks/dp_x
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const int M = 1e4 + 5;

tuple<int, int, int> a[N];
long long dp[N][M];

bool comp(tuple<int, int, int> x, tuple<int, int, int> y) {
    int l = get<0>(x) - get<1>(y);
    int r = get<0>(y) - get<1>(x);
    return l > r;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int w, s, v;
        cin >> w >> s >> v;
        a[i] = make_tuple(s, w, v);
        for (int j = 0; j < M; j++) {
            dp[i][j] = -1;
        }
    }
    sort(a, a + n, comp);
    for (int i = 0; i < n; i++) {
        auto [s, w, v] = a[i];
        if (i == 0) {
            dp[0][s] = v;
        } else {
            for (int j = 0; j < M; j++) {
                if (dp[i - 1][j] == -1) {
                    continue;
                }
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                int k = min(j - w, s);
                if (k >= 0) {
                    dp[i][k] = max(dp[i][k], dp[i - 1][j] + v);
                }
            }
            dp[i][s] = max(dp[i][s], (long long)v);
        }
    }
    long long ans = 0;
    for (int j = 0; j < M; j++) {
        ans = max(ans, dp[n - 1][j]);
    }
    cout << ans;
    return 0;
}
