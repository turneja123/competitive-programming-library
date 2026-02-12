//https://acm.timus.ru/problem.aspx?space=1&num=2119
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int K = 20;

int tin[N], tout[N];
int up[N][K];
int timer = 0, euler = 0;
vector<pair<int, int>> adj[N];
int parent[N];
int sz[N];
int edges[N];
int depth[N];
ll path[N];
int vals[N];
int tour[N];

int mark[N];

int root = -1;
ll sum = 0;

set<int> subgraph;

int dfs(int v, int p, int ct) {
    tour[v] = euler++;
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i < K; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        int u = it->first, wt = it->second;
        if (u != p) {
            vals[u] = wt;
            path[u] = path[v] + wt;
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
    for (int i = K - 1; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

int segtree[4 * N];

int rsq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return rsq(l, mid, lq, rq, 2 * node + 1) + rsq(mid + 1, r, lq, rq, 2 * node + 2);
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
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

ll calc(int a, int b, int f) {
    return path[a] - path[b] + (f == 0 ? vals[b] : 0);
}

int kth(int v, int k) {
    int i = 0;
    while (k > 0) {
        int j = 1 << i, c = k & j;
        if (c != 0) {
            v = up[v][i];
            k ^= j;
        }
        i++;
    }
    return v;
}

void add_node(int u, int n) {
    subgraph.insert(u);
    assert(mark[u] == 0);
    if (root == -1) {
        root = u;
        update(0, n - 1, tour[u], 1, 0);
        mark[u] = 1;
        return;
    }
    int l = lca(u, root);
    if (l != root) {
        sum += calc(u, l, 1);
        sum += calc(root, l, 1);
        update(0, n - 1, tour[u], 1, 0);
        root = l;
    } else {
        int ct = rsq(0, n - 1, tour[u], tour[u] + sz[u] - 1, 0);
        if (ct == 0) {
            int l = 0, r = depth[u] - depth[root], leaf = u;
            while (l <= r) {
                int mid = (l + r) / 2;
                int ancestor = kth(u, mid), cur = rsq(0, n - 1, tour[ancestor], tour[ancestor] + sz[ancestor] - 1, 0);
                if (cur == 0) {
                    leaf = ancestor;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            sum += calc(u, leaf, ((leaf == root) ? 1 : 0));
            update(0, n - 1, tour[u], 1, 0);
        } else {
            update(0, n - 1, tour[u], 1, 0);
        }
    }
    mark[u] = 1;
    return;
}

void delete_node(int u, int n) {
    subgraph.erase(u);
    update(0, n - 1, tour[u], 0, 0);
    if (subgraph.size() < 2) {
        sum = 0;
        mark[u] = 0;
        if (subgraph.empty()) {
            root = -1;
        } else {
            root = *subgraph.begin();
        }
        return;
    }
    int r = depth[u] - depth[root], ancestor = kth(u, r - 1);
    if (u == root || rsq(0, n - 1, tour[ancestor], tour[ancestor] + sz[ancestor] - 1, 0) == 0) {
        sum -= calc(u, root, 1);
        int test = *subgraph.begin();
        if (test != root) {
            int l = 0, r = depth[test] - depth[root], new_root = root;
            while (l <= r) {
                int mid = (l + r) / 2;
                int ancestor = kth(test, mid), cur = rsq(0, n - 1, tour[ancestor], tour[ancestor] + sz[ancestor] - 1, 0);
                if (cur == subgraph.size()) {
                    new_root = ancestor;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (new_root != root) {
                sum -= calc(new_root, root, 1);
                root = new_root;
            }
        }
        mark[u] = 0;
        return;
    }
    int ct = rsq(0, n - 1, tour[u], tour[u] + sz[u] - 1, 0);
    if (ct == 0) {
        int l = 0, r = depth[u] - depth[root], leaf = u;
        while (l <= r) {
            int mid = (l + r) / 2;
            int ancestor = kth(u, mid), cur = rsq(0, n - 1, tour[ancestor], tour[ancestor] + sz[ancestor] - 1, 0);
            if (cur == 0) {
                leaf = ancestor;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        sum -= calc(u, leaf, 0);
    }
    mark[u] = 0;
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
    }
    dfs(0, 0, 1);
    cin >> q;
    for (int i = 0; i < q; i++) {
        char t;
        cin >> t;
        int u;
        cin >> u;
        u--;
        if (!mark[u]) {
            add_node(u, n);
        } else {
            delete_node(u, n);
        }
        cout << sum << endl;

    }

    return 0;
}
