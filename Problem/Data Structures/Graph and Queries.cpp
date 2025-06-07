//https://codeforces.com/problemset/problem/1416/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int K = 20;

tuple<int, int, int> edges[N];

int parent[N];
int tin[N];
int up[K][N];
int val[N];
int sz[N];
int a[N];

int timer = 0;
vector<int> adj[N];

int dsu_find(int u) {
    if (parent[u] == u) {
        return u;
    }
    return parent[u] = dsu_find(parent[u]);
}

void add_edge(int u, int v, int e) {
    u = dsu_find(u), v = dsu_find(v);
    if (u == v) {
        return;
    }
    parent[u] = e;
    parent[v] = e;
    parent[e] = e;
    adj[e].push_back(v);
    adj[e].push_back(u);
    adj[u].push_back(e);
    adj[v].push_back(e);
    return;
}

void dfs(int u, int p, int n) {
    sz[u] = 1;
    tin[u] = timer;
    a[timer++] = (u >= n ? 0 : val[u]);
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, n);
            sz[u] += sz[v];
        }
    }
}

struct Node {
    int val;
    int pos;
    Node() {
        val = 0; pos = 0;
    }
    Node(int _val, int _pos) {
        val = _val, pos = _pos;
    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node;
    if (left.val > right.val) {
        node.val = left.val;
        node.pos = left.pos;
    } else {
        node.val = right.val;
        node.pos = right.pos;
    }
    return node;
}

Node rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        Node sentinel = Node();
        return sentinel;
    }

    int mid = (l + r) / 2;
    return combine(rmq(l, mid, lq, rq, 2 * node + 1),
               rmq(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] = Node(val, l);
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(a[l], l);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
        parent[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        edges[i] = make_tuple(q, u, v);
    }
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; i++) {
        int t, j;
        cin >> t >> j;
        j--;
        if (t == 1) {
            queries.push_back(make_pair(i, j));
        } else {
            get<0>(edges[j]) = i;
        }
    }
    sort(edges, edges + m);
    int e = n;
    for (int i = m - 1; i >= 0; i--) {
        auto [t, u, v] = edges[i];
        add_edge(u, v, e);
        val[e] = t;
        e++;
    }
    for (int i = 0; i < e; i++) {
        if (dsu_find(i) == i) {
            dfs(i, i, n);
        }
    }
    build(0, e - 1, 0);
    for (auto [t, u] : queries) {
        for (int i = K - 1; i >= 0; i--) {
            if (val[up[i][u]] > t) {
                u = up[i][u];
            }
        }
        Node node = rmq(0, e - 1, tin[u], tin[u] + sz[u] - 1, 0);
        cout << node.val << endl;
        if (node.val != 0) {
            update(0, e - 1, node.pos, 0, 0);
        }
    }
    return 0;
}
