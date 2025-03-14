//https://atcoder.jp/contests/abc324/tasks/abc324_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long double INF = -1e18;

vector<tuple<int, int, int>> adj[N];
long double dp[N];

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, b, c;
        cin >> u >> v >> b >> c;
        u--, v--;
        adj[v].push_back(make_tuple(u, b, c));
    }
    long double l = 0.0, r = 1e4 + 1.0, ans = 0.0;
    for (int it = 0; it < 200; it++) {
        long double mid = (l + r) / (long double)2.0;
        for (int i = 0; i < n; i++) {
            dp[i] = INF;
        }
        dp[0] = 0;
        for (int i = 1; i < n; i++) {
            for (auto [u, b, c] : adj[i]) {
                dp[i] = max(dp[i], dp[u] + (long double)b - (long double)c * mid);
            }
        }
        if (dp[n - 1] >= 0) {
            ans = mid;
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << ans;
    return 0;
}
