//https://www.codechef.com/problems/CHEFCOMP
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int K = 20;
const long long INF = 1e18;

tuple<int, int, int> edges[N];

int parent[N];
int tin[N];
int up[K][N];
int val[N];
int sz[N];

int id[N];
int p[N];
int cost[N];
int ans[N];
long long a[N];

int timer = 0;
vector<pair<int, int>> adj_original[N];
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
    id[timer] = u;
    a[timer++] = (u >= n ? INF : (ll)val[u]);
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
    long long val;
    long long lazy;
    int pos;
    Node() {
        lazy = 0;
        val = INF;
        pos = -1;
    }
    Node(long long _val, int _pos) {
        val = _val;
        pos = _pos;
        lazy = 0;
    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.val < right.val) {
        node.val = left.val;
        node.pos = left.pos;
    } else {
        node.val = right.val;
        node.pos = right.pos;
    }
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy += segtree[parent].lazy;
}

void apply(int node, int l, int r) {
    segtree[node].val += segtree[node].lazy;
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, long long add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void setUpdate(int node, int l, int r, int ind, long long val) {
    apply(node, l, r);
    if (l == r) {
        segtree[node] = Node(val, l);
        return;
    }

    int mid = (l + r) / 2;
    if (ind <= mid) {
        setUpdate(node * 2 + 1, l, mid, ind, val);
    } else {
        setUpdate(node * 2 + 2, mid + 1, r, ind, val);
    }
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        Node sentinel;
        return sentinel;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
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
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            edges[i] = make_tuple(n, u, v);
            adj_original[u].push_back({v, i});
            adj_original[v].push_back({u, i});
        }
        for (int i = 0; i < n; i++) {
            cin >> p[i];
            p[i]--;
            parent[i] = i;
            ans[i] = -1;
            for (auto [v, e] : adj_original[p[i]]) {
                if (get<0>(edges[e]) == n) {
                    get<0>(edges[e]) = i;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            cin >> cost[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> val[i];
        }
        sort(edges, edges + n - 1);
        int e = n;
        for (int i = n - 2; i >= 0; i--) {
            auto [t, u, v] = edges[i];
            add_edge(u, v, e);
            val[e] = t;
            e++;
        }
        int root = dsu_find(0);
        dfs(root, root, n);
        build(0, e - 1, 0);
        for (int i = 0; i < n; i++) {
            int u = p[i];
            for (int k = K - 1; k >= 0; k--) {
                if (val[up[k][u]] >= i) {
                    u = up[k][u];
                }
            }
            incUpdate(0, 0, e - 1, tin[u], tin[u] + sz[u] - 1, -cost[p[i]]);
            while (1) {
                Node node = query(0, e - 1, tin[u], tin[u] + sz[u] - 1, 0);
                if (node.val > 0) {
                    break;
                }
                ans[id[node.pos]] = i + 1;
                setUpdate(0, 0, e - 1, node.pos, INF);
            }
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < e; i++) {
            adj[i].clear();
            adj_original[i].clear();
        }
        timer = 0;
    }

    return 0;
}
