//solution for http://www.usaco.org/index.php?page=viewproblem2&cpid=576
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

list<int> adj[N];
vector<int> tin, tout, depth;
vector<vector<int>> up;
int timer = 0, euler = 0, lg;

int sz[N];
int tour[N];

int dfs(int v, int p, int ct) {
    tour[v] = euler++;
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : adj[v]) {
        if (u != p) {
            depth[u] = depth[v] + 1;
            ct += dfs(u, v, 1);
        }
    }
    tout[v] = ++timer;
    return sz[v] = ct;
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

int a[N];
int segtree[4 * N];

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        a[ind] = val;
        segtree[node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

int getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    if (l >= lq && r <= rq) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
}

int main() {
    IOS;
    //freopen("maxflow.in", "r", stdin);
    //freopen("maxflow.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    lg = ceil(log2(n));
    up.assign(n, vector<int>(lg + 1));
    tin.resize(n);
    tout.resize(n);
    depth.resize(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0, 0);
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int l = lca(u, v);
        update(0, n - 1, tour[u], a[tour[u]] + 1, 0);
        update(0, n - 1, tour[v], a[tour[v]] + 1, 0);
        update(0, n - 1, tour[l], a[tour[l]] - 1, 0);
        if (l != 0) {
            update(0, n - 1, tour[up[l][0]], a[tour[up[l][0]]] - 1, 0);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, getSum(0, n - 1, tour[i], tour[i] + sz[i] - 1, 0));
    }
    cout << ans << endl;

    return 0;
}
