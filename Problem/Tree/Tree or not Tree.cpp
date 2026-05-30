//https://codeforces.com/contest/117/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 19;
const int INF = 1e9;

int timer = 0;
int euler = 0;
int tin[N];
int tout[N];
int pos[N];
int up[K][N];
vector<int> g[N];
vector<int> adj[N];
int sz[N];
int depth[N];
int tail[N];
bool head[N];
int edges[N];
int in[N];
int root[N];
int id[N];
int par[N];
int vis[N];
int found = 0;
int rt;
vector<int> cyc;

void dfs_cycle(int u, int p) {
    if (found) {
        return;
    }
    vis[u] = 1;
    par[u] = p;
    for (int v : g[u]) {
        if (v == p) {
            continue;
        }
        if (!vis[v]) {
            dfs_cycle(v, u);
            if (found) {
                return;
            }
        } else {
            found = 1;
            cyc.push_back(v);
            while (u != v) {
                cyc.push_back(u);
                u = par[u];
            }
            return;
        }
    }
}

void dfs(int u, int p) {
    tin[u] = ++timer;
    up[0][u] = p;
    root[u] = rt;
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

struct Node {
    int val;
    int ct;
    int lazy;
    Node() {
        lazy = 0;
        val = 0;
        ct = 0;
    }
    Node(int x) {
        lazy = 0;
        val = x;
        ct = 1;

    }
};

Node segtree[2][4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.val = min(left.val, right.val);
    if (left.val == node.val) {
        node.ct += left.ct;
    }
    if (right.val == node.val) {
        node.ct += right.ct;
    }
    return node;
}

void compose(int t, int parent, int child) {
    segtree[t][child].lazy ^= segtree[t][parent].lazy;
}

void apply(int t, int node, int l, int r) {
    if (!segtree[t][node].lazy) {
        return;
    }
    int len = r - l + 1;
    if (segtree[t][node].val == 1) {
        segtree[t][node].val = 0;
        segtree[t][node].ct = len;
    } else {
        if (segtree[t][node].ct == len) {
            segtree[t][node].val = 1;
            segtree[t][node].ct = len;
        } else {
            segtree[t][node].ct = len - segtree[t][node].ct;
        }
    }
    if (l != r) {
        compose(t, node, 2 * node + 1);
        compose(t, node, 2 * node + 2);
    }
    segtree[t][node].lazy = 0;
}

void incUpdate(int t, int node, int l, int r, int lq, int rq) {
    if (lq > rq || l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[t][node].lazy ^= 1;
        return;
    }
    apply(t, node, l, r);
    int mid = (l + r) / 2;
    incUpdate(t, node * 2 + 1, l, mid, lq, rq);
    incUpdate(t, node * 2 + 2, mid + 1, r, lq, rq);
    apply(t, 2 * node + 1, l, mid);
    apply(t, 2 * node + 2, mid + 1, r);
    segtree[t][node] = combine(segtree[t][2 * node + 1], segtree[t][2 * node + 2]);
}

void build(int t, int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[t][node] = Node(0);
        return;
    }
    int mid = (l + r) / 2;
    build(t, l, mid, node * 2 + 1);
    build(t, mid + 1, r, node * 2 + 2);
    segtree[t][node] = combine(segtree[t][2 * node + 1], segtree[t][2 * node + 2]);
}

void upd(int u, int par, int n) {
    while (1) {
        if (tail[u] == tail[par]) {
            incUpdate(0, 0, 0, n - 1, pos[par] + 1, pos[u]);
            break;
        }
        incUpdate(0, 0, 0, n - 1, pos[tail[u]], pos[u]);
        u = up[0][tail[u]];
    }
}

void upd_cyc(int l, int r, int n) {
    if (l == r) {
        return;
    }
    if (l < r) {
        incUpdate(1, 0, 0, n - 1, l, r - 1);
    } else {
        incUpdate(1, 0, 0, n - 1, l, n - 1);
        incUpdate(1, 0, 0, n - 1, 0, r - 1);
    }
}

int get(int t, int n) {
    apply(t, 0, 0, n - 1);
    if (segtree[t][0].val == 1) {
        return n;
    }
    return n - segtree[t][0].ct;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        head[i] = true;
    }

    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_cycle(0, 0);
    int c = cyc.size();
    for (int i = 0; i < c; i++) {
        in[cyc[i]] = 1;
        id[cyc[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int v : g[i]) {
            if (i < v && !(in[i] && in[v])) {
                adj[i].push_back(v);
                adj[v].push_back(i);
            }
        }
    }
    for (int x : cyc) {
        rt = x;
        depth[x] = 0;
        edges[x] = 0;
        dfs(x, x);
        dfs_markedges(x, x);
    }

    build(0, 0, n - 1, 0);
    build(1, 0, c - 1, 0);
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
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (root[u] == root[v]) {
            int l = lca(u, v);
            upd(u, l, n);
            upd(v, l, n);
        } else {
            upd(u, root[u], n);
            upd(v, root[v], n);
            int a = id[root[u]], b = id[root[v]], d = (b - a + c) % c, e = c - d;
            if (d < e) {
                upd_cyc(a, b, c);
            } else if (e < d) {
                upd_cyc(b, a, c);
            } else {
                if (cyc[(a + 1) % c] < cyc[(a - 1 + c) % c]) {
                    upd_cyc(a, b, c);
                } else {
                    upd_cyc(b, a, c);
                }
            }
        }
        int all = get(0, n) + get(1, c);
        int add = 0;
        apply(1, 0, 0, c - 1);
        if (segtree[1][0].val == 1) {
            add = 1;
        }
        cout << n - all + add << endl;
    }
    return 0;
}
