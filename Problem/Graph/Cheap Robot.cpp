//https://codeforces.com/contest/1253/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const int K = 20;

int parent[N];
int tin[N];
int tout[N];
int up[K][N];
ll wt[N];
int timer = 0;

vector<int> adj[N];

int dsu_find(int u) {
    if (parent[u] == u) {
        return u;
    }
    return parent[u] = dsu_find(parent[u]);
}

void add_edge(int u, int v, int &e, ll w) {
    u = dsu_find(u), v = dsu_find(v);
    if (u == v) {
        return;
    }
    wt[e] = w;
    parent[u] = e;
    parent[v] = e;
    parent[e] = e;
    adj[e].push_back(v);
    adj[e].push_back(u);
    adj[u].push_back(e);
    adj[v].push_back(e);
    e++;
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

vector<pair<int, int>> adj_g[N];

int main() {
    IOS;
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    int e = k;
    for (int i = 0; i < k; i++) {
        parent[i] = i;
    }
    vector<tuple<int, int, int>> ed_orig;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        ed_orig.push_back({u, v, w});
        adj_g[u].push_back({v, w});
        adj_g[v].push_back({u, w});
    }
    vector<ll> dist(n, 0);
    vector<int> who(n, 0);

    for (int i = 0; i < n; i++) {
        dist[i] = 1e18;
    }
    priority_queue<pair<ll, int>> pq;
    for (int i = 0; i < k; i++) {
        dist[i] = 0;
        who[i] = i;
        pq.push({0, i});
    }
    while (pq.size()) {
        auto [x, u] = pq.top();
        x = -x;
        pq.pop();
        if (dist[u] != x) {
            continue;
        }
        for (auto [v, w] : adj_g[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                who[v] = who[u];
                pq.push({-dist[v], v});
            }
        }
    }
    vector<tuple<ll, int, int>> edges;

    for (auto [u, v, w] : ed_orig) {
        edges.push_back({dist[u] + w + dist[v], who[u], who[v]});
    }
    sort(edges.begin(), edges.end());

    for (auto [w, u, v] : edges) {
        add_edge(u, v, e, w);
    }
    int root = dsu_find(0);
    dfs(root, root);
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int l = lca(u, v);
        cout << wt[l] << endl;
    }


    return 0;
}
