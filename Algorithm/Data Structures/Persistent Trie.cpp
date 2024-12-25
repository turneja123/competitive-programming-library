//https://toph.co/p/yet-another-xor-tree-problem
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;
const int K = 30;
const int MAX = 1e7 + 5;

struct Node {
    int ct;
    int left;
    int right;
    Node() : ct(0), left(-1), right(-1) {}
};

vector<pair<int, int>> adj[N];
int a[N];
int root[N];
Node nodes[MAX];
int idx = 0;

int timer = 0;
vector<int> tin, tout;
vector<vector<int>> up;
int lg;

int query(int node_prev, int node, int d, int val, int ans) {
    if (d == -1) {
        return ans;
    }
    int c = val & (1 << d);
    if (c == 0) {
        int ct = (nodes[node].right == -1 ? 0 : nodes[nodes[node].right].ct);
        if (node_prev != -1) {
            ct -= (nodes[node_prev].right == -1 ? 0 : nodes[nodes[node_prev].right].ct);
        }
        if (ct > 0) {
            return query((node_prev == -1 ? -1 : nodes[node_prev].right), nodes[node].right, d - 1, val, ans ^ (1 << d));
        } else {
            return query((node_prev == -1 ? -1 : nodes[node_prev].left), nodes[node].left, d - 1, val, ans);
        }
    } else {
        int ct = (nodes[node].left == -1 ? 0 : nodes[nodes[node].left].ct);
        if (node_prev != -1) {
            ct -= (nodes[node_prev].left == -1 ? 0 : nodes[nodes[node_prev].left].ct);
        }
        if (ct > 0) {
            return query((node_prev == -1 ? -1 : nodes[node_prev].left), nodes[node].left, d - 1, val, ans ^ (1 << d));
        } else {
            return query((node_prev == -1 ? -1 : nodes[node_prev].right), nodes[node].right, d - 1, val, ans);
        }
    }
}

void add(int node_prev, int node, int d, int val) {
    if (d < 0) {
        return;
    }
    int c = val & (1 << d);
    if (c == 0) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[nodes[node].left].ct = 1;
        if (node_prev != -1) {
            nodes[nodes[node].left].ct += nodes[nodes[node_prev].left].ct;
            nodes[node].right = nodes[node_prev].right;
        }
        add((node_prev == -1 ? -1 : nodes[node_prev].left), nodes[node].left, d - 1, val);
        return;
    } else {
        nodes[node].right = idx;
        nodes[idx++] = Node();
        nodes[nodes[node].right].ct = 1;
        if (node_prev != -1) {
            nodes[nodes[node].right].ct += nodes[nodes[node_prev].right].ct;
            nodes[node].left = nodes[node_prev].left;
        }
        add((node_prev == -1 ? -1 : nodes[node_prev].right), nodes[node].right, d - 1, val);
        return;
    }
}

void dfs(int u, int p, int cur_root) {
    if (cur_root == -1) {
        root[u] = idx;
        nodes[idx++] = Node();
    } else {
        root[u] = idx;
        nodes[idx++] = Node();
        add(cur_root, root[u], K - 1, a[u]);
    }
    tin[u] = timer++;
    up[u][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }

    for (auto [v, wt] : adj[u]) {
        if (v != p) {
            a[v] = a[u] ^ wt;
            dfs(v, u, root[u]);
        }
    }
    tout[u] = timer++;
    return;
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

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n - 1; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            adj[u].push_back(make_pair(v, wt));
            adj[v].push_back(make_pair(u, wt));
        }
        lg = ceil(log2(n));
        up.assign(n, vector<int>(lg + 1));
        tin.resize(n);
        tout.resize(n);
        timer = 0;
        dfs(0, 0, -1);
        for (int i = 0; i < q; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            if (u == v) {
                cout << 0 << endl;
                continue;
            }
            int l = lca(u, v);
            if (u == l) {
                cout << max(a[v] ^ a[u], query(root[u], root[v], K - 1, a[u], 0)) << endl;
                continue;
            }
            int ans = max(a[u] ^ a[l], query(root[l], root[u], K - 1, a[u], 0));
            if (v != l) {
                int pref = a[u] ^ a[l];
                ans = max(ans, query(root[l], root[v], K - 1, pref ^ a[l], 0));
            }
            cout << ans << endl;
        }
        idx = 0;
        up.clear();
        tin.clear();
        tout.clear();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }

    return 0;
}
