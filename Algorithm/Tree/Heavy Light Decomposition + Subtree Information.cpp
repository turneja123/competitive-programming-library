//https://www.hackerrank.com/challenges/subtrees-and-paths/problem
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
vector<int> adj[N];
int sz[N];
int depth[N];
int tail[N];
bool head[N];
int edges[N];

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

struct Node {
    int val;
    int lazy;
    Node() {
        lazy = 0;
    }
    Node(int x) {
        lazy = 0;
        val = x;

    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.val = max(left.val, right.val);
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

int query(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r || lq > rq) {
        return -INF;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node].val;
    }
    int mid = (l + r) / 2;
    return max(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(0);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int calc(int u, int par, int flag, int n) {
    int ans = -INF;
    while (1) {
        if (tail[u] == tail[par]) {
            ans = max(ans, query(0, n - 1, pos[par] + flag, pos[par] + depth[u] - depth[par], 0));
            break;
        }
        ans = max(ans, query(0, n - 1, pos[tail[u]], pos[tail[u]] + depth[u] - depth[tail[u]], 0));
        u = up[0][tail[u]];
    }
    return ans;
}


int main() {
    IOS;
    int n, q;
    cin >> n;
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
    build(0, n - 1, 0);
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

    cin >> q;
    for (int i = 0; i < q; i++) {
        string t; int u, v;
        cin >> t >> u >> v;
        if (t == "max") {
            u--, v--;
            if (depth[u] > depth[v]) {
                swap(u, v);
            }
            int l = lca(u, v);
            int ans = calc(v, l, 0, n);
            if (u != l) {
                ans = max(ans, calc(u, l, 1, n));
            }
            cout << ans << endl;
        } else {
            u--;
            incUpdate(0, 0, n - 1, pos[u], pos[u] + sz[u] - 1, v);
        }
    }
    return 0;
}
