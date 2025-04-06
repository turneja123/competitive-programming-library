//https://www.spoj.com/problems/SIMPLEPATH/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 1e9 + 7;

int sz[N];
long long dp[N];
long long sum[N];
vector<pair<int, int>> adj[N];

void dfs(int u, int p) {
    sz[u] = 1;
    for (auto [v, wt] : adj[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
            dp[u] = (dp[u] + dp[v]) % M;
            sum[u] = (sum[u] + sum[v] + (long long)sz[v] * wt) % M;
        }
    }
    for (auto [v, wt] : adj[u]) {
        if (v != p) {
            dp[u] = (dp[u] + (sum[v] + (long long)sz[v] * wt) * (sz[u] - sz[v])) % M;
        }
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            adj[u].push_back(make_pair(v, wt));
            adj[v].push_back(make_pair(u, wt));
        }
        dfs(0, 0);
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + dp[i]) % M;
            dp[i] = 0, sum[i] = 0;
            adj[i].clear();
        }
        cout << "Case " << tt << ": " << ans << endl;
    }

    return 0;
}
