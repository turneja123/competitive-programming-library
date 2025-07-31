//https://olympicode.rs/problem/37
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

int sz[N];
bool seen_c[N];
int parent_c[N];
vector<pair<int, int>> adj[N];
int val[N];
long long dist[N];

long long ans = 0;

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (auto [v, wt]  : adj[u]) {
        if (v != p && !seen_c[v] && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

vector<pair<long long, int>> subtree[N];

void dfs_depth(int u, int p, int c, int cent) {
    if (val[u] != INF) {
        if (val[cent] != INF) {
            long long cur = dist[u] / (val[u] + val[cent]);
            if (dist[u] % (val[u] + val[cent]) != 0) {
                cur++;
            }
            ans = max(ans, cur);
        }
        subtree[c].push_back({dist[u], val[u]});
    }
    for (auto [v, wt]  : adj[u]) {
        if (v != p && !seen_c[v]) {
            dist[v] = dist[u] + wt;
            dfs_depth(v, u, c, cent);
        }
    }
    return;
}

void build(int u, int p) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;

    for (auto [v, wt]  : adj[c]) {
        if (!seen_c[v]) {
            dist[v] = wt;
            dfs_depth(v, v, v, c);
        }
    }
    long long l = ans, r = 1e12;
    while (l <= r) {
        long long mid = (l + r) / 2;
        long long mx1 = -1e18, mx2 = -1e18;
        for (auto [v, wt] : adj[c]) {
            if (!seen_c[v]) {
                long long best = -1e18;
                for (auto [x, y] : subtree[v]) {
                    best = max(best, x - mid * y);
                }
                if (best > mx1) {
                    mx2 = mx1;
                    mx1 = best;
                } else if (best > mx2) {
                    mx2 = best;
                }
            }
        }
        if (mx1 + mx2 <= 0) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    for (auto [v, wt]  : adj[c]) {
        if (!seen_c[v]) {
            subtree[v].clear();
        }
    }
    for (auto [v, wt]  : adj[c]) {
        if (!seen_c[v]) {
            build(v, c);
        }
    }
    return;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        val[i] = INF;
    }
    for (int i = 1; i < n; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    for (int i = 0; i < m; i++) {
        int u, wt;
        cin >> u >> wt;
        u--;
        val[u] = min(val[u], wt);
    }
    build(0, -1);
    cout << ans;


    return 0;
}
