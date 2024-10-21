//https://www.spoj.com/problems/DISQUERY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 19;

vector<pair<int, int>> adj[N];
int a[N];
int up[K][N];
int mx[K][N];
int mn[K][N];

int depth[N];

int x, y;

void dfs(int u, int p) {
    up[0][u] = p;
    mx[0][u] = a[u];
    mn[0][u] = a[u];
    for (int k = 1; k < K; k++) {
        int v = up[k - 1][u];
        up[k][u] = up[k - 1][v];
        mx[k][u] = max(mx[k - 1][u], mx[k - 1][v]);
        mn[k][u] = min(mn[k - 1][u], mn[k - 1][v]);
    }
    for (pair<int, int> pr : adj[u]) {
        int v = pr.first, wt = pr.second;
        if (v != p) {
            a[v] = wt;
            depth[v] = depth[u] + 1;
            dfs(v, u);
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

void calc(int u, int d) {
    for (int k = K - 1; k >= 0; k--) {
        int c = d & (1 << k);
        if (c) {
            x = min(x, mn[k][u]), y = max(y, mx[k][u]);
            u = up[k][u];
        }
    }
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
    }
    dfs(0, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int l = lca(u, v);
        x = 1e9, y = 0;
        if (u != l) {
            int d = depth[u] - depth[l];
            calc(u, d);
        }
        if (v != l) {
            int d = depth[v] - depth[l];
            calc(v, d);
        }
        cout << x << " " << y << endl;
    }
    return 0;
}
