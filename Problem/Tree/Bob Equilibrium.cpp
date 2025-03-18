//https://dmoj.ca/problem/dmopc19c7p6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int INF = 1e9;

pair<int, int> a[N];
int sz[N];
bool seen_c[N];
int parent_c[N];
int depth[N];
int ans[N];

int is_store[N];
int depth_tree[N];
int need[N];
int tot[N];
int near[N];
int diff[N];

vector<int> stores;
vector<int> adj[N];

vector<int> tin, tout;
vector<vector<int>> up;
int timer = 0, lg;

void dfs(int v, int p) {
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : adj[v]) {
        if (u != p) {
            depth_tree[u] = depth_tree[v] + 1;
            dfs(u, v);
        }
    }
    tout[v] = timer++;
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
    for (int i = lg; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (int v : adj[u]) {
        if (v != p && !seen_c[v] && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

int mn;

void dfs_depth1(int u, int p) {
    if (is_store[u]) {
        mn = min(mn, depth[u]);
    }
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + 1;
            dfs_depth1(v, u);
        }
    }
    return;
}

void dfs_depth2(int u, int p) {
    near[u] = min(near[u], mn + depth[u]);
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + 1;
            dfs_depth2(v, u);
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

    mn = INF;
    if (is_store[c]) {
        mn = 0;
    }
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = 1;
            dfs_depth2(v, v);
            dfs_depth1(v, v);
        }
    }
    near[c] = min(near[c], mn);
    reverse(adj[c].begin(), adj[c].end());
    mn = INF;
    if (is_store[c]) {
        mn = 0;
    }
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = 1;
            dfs_depth2(v, v);
            dfs_depth1(v, v);
        }
    }
    reverse(adj[c].begin(), adj[c].end());
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            build(v, c);
        }
    }
    return;
}

void dfs1(int u, int p, int add) {
    if (need[u] - depth[u] >= 0) {
        diff[0] += add;
        diff[need[u] - depth[u] + 1] -= add;
    }
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + 1;
            dfs1(v, u, add);
        }
    }
    return;
}

void dfs2(int u, int p, int sum) {
    sum += diff[depth[u]];
    tot[u] += sum;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs2(v, u, sum);
        }
    }
    return;
}


void build2(int u, int p) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = 1;
            dfs1(v, v, 1);
        }
    }
    if (need[c] >= 0) {
        diff[0]++;
        diff[need[c] + 1]--;
    }

    tot[c] += diff[0];

    for (int v : adj[c]) {
        if (!seen_c[v]) {
            dfs1(v, v, -1);
            dfs2(v, v, diff[0]);
            dfs1(v, v, 1);
        }
    }
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            dfs1(v, v, -1);
        }
    }
    if (need[c] >= 0) {
        diff[0]--;
        diff[need[c] + 1]++;
    }

    for (int v : adj[c]) {
        if (!seen_c[v]) {
            build2(v, c);
        }
    }
    return;
}


int main() {
    IOS;
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    stores.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> stores[i];
        stores[i]--;
        is_store[stores[i]] = true;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        a[i].first--;
        near[i] = INF;
    }
    build(0, -1);
    lg = ceil(log2(n));
    up.assign(n, vector<int>(lg + 1));
    tin.resize(n);
    tout.resize(n);
    dfs(0, 0);

    for (int i = 0; i < n; i++) {
        int d = near[i];
        int l = lca(i, a[i].first);
        int fav = depth_tree[i] + depth_tree[a[i].first] - 2 * depth_tree[l];
        if (fav <= d + a[i].second) {
            need[i] = fav - a[i].second - 1;
        } else {
            need[i] = d;
        }
    }

    for (int i = 0; i < n; i++) {
        seen_c[i] = false;
    }
    build2(0, -1);
    for (int i = 0; i < n; i++) {
        cout << tot[i] << " ";
    }

    return 0;
}
