//https://codeforces.com/contest/1628/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 6e5 + 5;
const int K = 21;
const int INF = 2e9;

int parent[N];
int tin[N];
int tout[N];
int up[K][N];
int tour[N];
int val[N];
int pos[N];
int timer = 0;
int euler = 0;

vector<int> adj[N];

int dsu_find(int u) {
    if (parent[u] == u) {
        return u;
    }
    return parent[u] = dsu_find(parent[u]);
}

void add_edge(int u, int v, int e, int wt) {
    u = dsu_find(u), v = dsu_find(v);
    if (u == v) {
        return;
    }
    parent[u] = e;
    parent[v] = e;
    parent[e] = e;
    val[e] = wt;
    adj[e].push_back(v);
    adj[e].push_back(u);
    adj[u].push_back(e);
    adj[v].push_back(e);
    return;
}

void dfs(int u, int p) {
    tin[u] = timer++;
    tour[euler] = u;
    pos[u] = euler++;
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

struct Node {
    int setVal;
    int mn;
    int mx;
    int mnActual;
    int mxActual;
    Node() {
        setVal = 0;
        mn = INF, mnActual = INF;
        mx = -INF, mxActual = -INF;
    }
    Node(int x) {
        setVal = 0;
        mn = INF, mnActual = x;
        mx = -INF, mxActual = x;
    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.mn = min(left.mn, right.mn);
    node.mnActual = min(left.mnActual, right.mnActual);

    node.mx = max(left.mx, right.mx);
    node.mxActual = max(left.mxActual, right.mxActual);
    return node;
}

void compose(int parent, int child) {
    segtree[child].setVal = segtree[parent].setVal;
}

void apply(int node, int l, int r) {
    if (segtree[node].setVal == 1) {
        segtree[node].mn = segtree[node].mnActual;
        segtree[node].mx = segtree[node].mxActual;
    } else if (segtree[node].setVal == 2) {
        segtree[node].mn = INF;
        segtree[node].mx = -INF;
    }
    if (l != r && segtree[node].setVal > 0) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].setVal = 0;
}

void setUpdate(int node, int l, int r, int lq, int rq, int val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].setVal = val;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

pair<int, int> query(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return {INF, -INF};
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return {segtree[node].mn, segtree[node].mx};
    }
    int mid = (l + r) / 2;
    pair<int, int> lf = query(l, mid, lq, rq, 2 * node + 1);
    pair<int, int> rt = query(mid + 1, r, lq, rq, 2 * node + 2);
    return {min(lf.first, rt.first), max(lf.second, rt.second)};
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(pos[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        val[i] = -1;
    }
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        edges.push_back({wt, u, v});
    }
    sort(edges.begin(), edges.end());
    int e = n;
    for (auto [wt, u, v] : edges) {
        add_edge(u, v, e, wt);
        e++;
    }
    int root = dsu_find(0);
    dfs(root, root);
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t < 3) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            setUpdate(0, 0, n - 1, l, r, t);
        } else {
            int x;
            cin >> x;
            x--;
            pair<int, int> v = query(0, n - 1, 0, n - 1, 0);
            int ans = -1;
            if (v.first != INF) {
                int y = tour[v.first];
                int l = lca(x, y);
                ans = max(ans, val[l]);
            }
            if (v.second != -INF) {
                int y = tour[v.second];
                int l = lca(x, y);
                ans = max(ans, val[l]);
            }
            cout << ans << endl;
        }
    }
    return 0;
}
