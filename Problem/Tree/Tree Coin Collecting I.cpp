//https://cses.fi/problemset/task/3114/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;
const int K = 19;

int a[N];
int up[K][N];
int mn[K][N];

vector<int> adj[N];

int depth[N];
int subtree[N];
int dp[N];

void dfs_subtree(int u, int p) {
    if (a[u]) {
        subtree[u] = 0;
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs_subtree(v, u);
            if (subtree[v] + 1 < subtree[u]) {
                subtree[u] = subtree[v] + 1;
            }
        }
    }
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dp[v] = min(dp[u] + 1, subtree[u] + 1);
            if (a[u]) {
                dp[v] = min(dp[v], 1);
            }
            dfs(v, u);
        }
    }
}

void dfs_build(int u, int p) {
    up[0][u] = p;
    mn[0][u] = subtree[u];
    for (int k = 1; k < K; k++) {
        int v = up[k - 1][u];
        up[k][u] = up[k - 1][v];
        mn[k][u] = min(mn[k - 1][u], mn[k - 1][v]);
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs_build(v, u);
        }
    }
    return;
}

int lca(int u, int v) {
    if (depth[v] > depth[u]) {
        swap(u, v);
    }
    int x = depth[u] - depth[v];
    for (int k = K - 1; k >= 0; k--) {
        int c = x & (1 << k);
        if (c) {
            u = up[k][u];
        }
    }
    if (u == v) {
        return u;
    }
    for (int k = K - 1; k >= 0; k--) {
        if (up[k][u] != up[k][v]) {
            u = up[k][u], v = up[k][v];
        }
    }
    return up[0][u];
}

int calc(int u, int d) {
    int ans = INF;
    for (int k = K - 1; k >= 0; k--) {
        int c = d & (1 << k);
        if (c) {
            ans = min(ans, mn[k][u]);
            u = up[k][u];
        }
    }
    ans = min(ans, mn[0][u]);
    return ans;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dp[i] = INF;
        subtree[i] = INF;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs_subtree(0, 0);
    dfs(0, 0);
    dfs_build(0, 0);
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int l = lca(u, v);
        int best = min(subtree[l], dp[l]);
        if (u != l) {
            int d = depth[u] - depth[l];
            best = min(best, calc(u, d));
        }
        if (v != l) {
            int d = depth[v] - depth[l];
            best = min(best, calc(v, d));
        }
        cout << depth[u] + depth[v] - 2 * depth[l] + 2 * best << endl;
    }

    return 0;
}
