//https://codeforces.com/contest/609/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int K = 20;

int parent[N];
int tin[N];
int tout[N];
int up[K][N];
int val[N];
int timer = 0;
ll ans[N];

vector<int> adj[N];

int dsu_find(int u) {
    if (parent[u] == u) {
        return u;
    }
    return parent[u] = dsu_find(parent[u]);
}

void add_edge(int u, int v, int e) {
    parent[u] = e;
    parent[v] = e;
    parent[e] = e;
    adj[e].push_back(v);
    adj[e].push_back(u);
    adj[u].push_back(e);
    adj[v].push_back(e);
    return;
}

void dfs(int u, int p) {
    tin[u] = timer++;
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    tout[u] = timer++;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int k = K - 1; k >= 0; k--) {
        if (!is_ancestor(up[k][u], v)) {
            u = up[k][u];
        }
    }
    return up[0][u];
}


int main() {
    IOS;
    int n, m, q;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    vector<tuple<int, int, int, int>> edges;
    int e = n;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        edges.push_back({wt, u, v, i});
    }
    sort(edges.begin(), edges.end());
    ll s = 0;
    for (auto [wt, u, v, i] : edges) {
        u = dsu_find(u), v = dsu_find(v);
        if (u != v) {
            s += wt;
            val[e] = wt;
            add_edge(u, v, e);
            e++;
        }
    }
    int root = dsu_find(0);
    dfs(root, root);

    for (auto [wt, u, v, i] : edges) {
        int l = lca(u, v);
        ans[i] = s + wt - val[l];
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
