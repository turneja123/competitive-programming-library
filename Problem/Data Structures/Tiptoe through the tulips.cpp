//https://www.codechef.com/problems/TULIPS
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int K = 20;
const int INF = 1e9;

int parent[N];
int tin[N];
int tour[N];
int up[K][N];
int sz[N];
int val[N];
int timer = 0;

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
    tour[timer] = u;
    tin[u] = timer++;
    up[0][u] = p;
    sz[u] = 1;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
}

struct Node {
    int lazy;
    int val;
    int ct;

    Node() {
        lazy = 0, val = -INF, ct = 0;
    }
    Node(int x) {
        lazy = 0, val = x, ct = 1;
    }
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.val = max(left.val, right.val);
    if (left.val == node.val) {
        node.ct += left.ct;
    }
    if (right.val == node.val) {
        node.ct += right.ct;
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

void incUpdate(int node, int l, int r, int lq, int rq, int add) {
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

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        Node sentinel = Node();
        return sentinel;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node, int n) {
    if (l > r) {
        return;
    }
    if (l == r) {
        int x = (tour[l] < n) ? 1 : 0;
        segtree[node] = Node(x);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1, n);
    build(mid + 1, r, node * 2 + 2, n);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
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
        build(0, e - 1, 0, n);
        int q, x;
        cin >> q >> x;
        queue<tuple<int, int, int>> qu;
        for (int i = 0; i < q; i++) {
            int d, u, k;
            cin >> d >> u >> k;
            u--;
            while (qu.size() && get<0>(qu.front()) <= d) {
                auto [_, l, r] = qu.front();
                incUpdate(0, 0, e - 1, l, r, 1);
                qu.pop();
            }
            for (int j = K - 1; j >= 0; j--) {
                if (val[up[j][u]] <= k) {
                    u = up[j][u];
                }
            }
            Node node = query(0, e - 1, tin[u], tin[u] + sz[u] - 1, 0);
            if (node.val == 1) {
                cout << node.ct << endl;
            } else {
                cout << 0 << endl;
            }
            incUpdate(0, 0, e - 1, tin[u], tin[u] + sz[u] - 1, -1);
            qu.push({d + x, tin[u], tin[u] + sz[u] - 1});
        }

        for (int i = 0; i < e; i++) {
            adj[i].clear();
        }
        timer = 0;
    }

    return 0;
}
