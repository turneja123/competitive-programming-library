//https://codeforces.com/contest/2110/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

int b[N];
vector<pair<int, int>> adj[N];
int dp[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        for (int i = 0; i < m; i++) {
            int u, v, wt;
            cin >> u >> v >>wt;
            u--, v--;
            adj[v].push_back(make_pair(u, wt));
        }
        int l = 1, r = INF, ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            for (int i = 0; i < n; i++) {
                dp[i] = -1;
            }
            dp[0] = min(mid, b[0]);
            for (int i = 1; i < n; i++) {
                for (auto [u, wt] : adj[i]) {
                    if (dp[u] >= wt) {
                        dp[i] = max(dp[i], min(mid, dp[u] + b[i]));
                    }
                }
            }
            if (dp[n - 1] != -1) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }

    return 0;
}
