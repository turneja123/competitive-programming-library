//https://dmoj.ca/problem/bts17p7
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 18;

int timer = 0;
int euler = 0;
int tin[N];
int tout[N];
int pos[N];
int up[K][N];
vector<int> adj[N];
int sz[N];
int depth[N];
int tail[N];
bool head[N];
int edges[N];

ll lazy[4 * N];
ll lazy_a[4 * N];
ll segtree[4 * N];

void dfs(int u, int p) {
    tin[u] = ++timer;
    up[0][u] = p;
    sz[u] = 1;
    for (int i = 1; i < K; i++) {
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    tout[u] = ++timer;
    return;
}

void dfs_markedges(int u, int p) {
    pos[u] = euler++;
    int heavy = -1;
    for (int v : adj[u]) {
        if (v != p) {
            if (sz[v] >= sz[u] / 2 + sz[u] % 2) {
                edges[v] = 1;
                head[u] = false;
                heavy = v;
            } else {
                edges[v] = 0;
            }
        }
    }
    if (heavy != -1) {
        dfs_markedges(heavy, u);
    }
    for (int v : adj[u]) {
        if (v != p && v != heavy) {
            dfs_markedges(v, u);
        }
    }

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
    for (int i = K - 1; i >= 0; --i) {
        if (!is_ancestor(up[i][u], v)) {
            u = up[i][u];
        }
    }
    return up[0][u];
}

void apply(int l, int r, int node) {
    segtree[node] = segtree[node] + lazy[node] * (r - l + 1) + lazy_a[node] * (r - l + 1) * (r - l + 2) / 2;
    if (l != r) {
        lazy[2 * node + 1] += lazy[node];
        lazy_a[2 * node + 1] += lazy_a[node];
        lazy[2 * node + 2] += lazy[node] + lazy_a[node] * ((l + r) / 2 - l + 1);
        lazy_a[2 * node + 2] += lazy_a[node];
    }
    lazy[node] = 0;
    lazy_a[node] = 0;
}

void incUpdate(int l, int r, int node, int lq, int rq, ll add, ll add_a) {
    if (l > rq || r < lq || lq > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] += add + add_a * (l - lq - 1);
        lazy_a[node] += add_a;
        return;
    }
    apply(l, r, node);
    int mid = (l + r) / 2;
    incUpdate(l, mid, 2 * node + 1, lq, rq, add, add_a);
    incUpdate(mid + 1, r, 2 * node + 2, lq, rq, add, add_a);
    apply(l, mid, 2 * node + 1);
    apply(mid + 1, r, 2 * node + 2);
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

ll query(int l, int r, int node, int lq, int rq) {
    if (l > rq || r < lq) {
        return 0;
    }
    apply(l, r, node);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return query(l, mid, 2 * node + 1, lq, rq) + query(mid + 1, r, 2 * node + 2, lq, rq);
}

ll dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

int calc(int u, int v, int t) {
    int l = lca(u, v);
    int x = lca(u, t);
    int y = lca(v, t);
    if (depth[x] > depth[l]) {
        l = x;
    }
    if (depth[y] > depth[l]) {
        l = y;
    }
    return l;
}

void upd_up(int u, int p, int rt, ll add, int n) {
    while (1) {
        if (tail[u] == tail[p]) {
            incUpdate(0, n - 1, 0, pos[p], pos[u], add + depth[rt] - depth[p], -1);
            break;
        }
        incUpdate(0, n - 1, 0, pos[tail[u]], pos[u], add + depth[rt] - depth[tail[u]], -1);
        u = up[0][tail[u]];
    }
}

void upd_down(int u, int p, int rt, ll add, int n) {
    while (tail[u] != tail[p]) {
        incUpdate(0, n - 1, 0, pos[tail[u]], pos[u], add + depth[rt] + depth[tail[u]] - 2 * depth[p], 1);
        u = up[0][tail[u]];
    }
    if (u != p) {
        incUpdate(0, n - 1, 0, pos[p] + 1, pos[u], add + depth[rt] - depth[p] + 1, 1);
    }
}

void upd_path(int u, int v, ll add, int n) {
    int l = lca(u, v);
    upd_up(u, l, u, add, n);
    upd_down(v, l, u, add, n);
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        head[i] = true;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    dfs_markedges(0, 0);
    for (int i = 0; i < n; i++) {
        if (head[i]) {
            vector<int> path;
            int v = i;
            while (1) {
                path.push_back(v);
                if (edges[v] == 0) {
                    break;
                }
                v = up[0][v];
            }
            for (int u : path) {
                tail[u] = path.back();
            }
        }
    }

    for (int i = 0; i < q; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        u--, v--, t--;
        int l = calc(u, v, t);
        ll d = dist(l, t);
        upd_path(l, u, d, n);
        upd_path(l, v, d, n);
        incUpdate(0, n - 1, 0, pos[l], pos[l], -d, 0);
    }

    for (int i = 0; i < n; i++) {
        cout << query(0, n - 1, 0, pos[i], pos[i]) << " ";
    }
    return 0;
}
