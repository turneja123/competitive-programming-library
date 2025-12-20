//https://codeforces.com/contest/2174/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e18;
const int N = 2e5 + 5;
const int K = 18;

vector<pair<int, int>> adj[N];

int ct = 0;

const int MAX = 1e7 + 5;

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;
int root[N];
int val[N];

void build(int node, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    nodes[node].left = idx;
    nodes[idx++] = Node();
    nodes[node].right = idx;
    nodes[idx++] = Node();
    build(nodes[node].left, l, mid);
    build(nodes[node].right, mid + 1, r);
    return;
}

void update(int node_prev, int node, int l, int r, int ind, int val) {
    if (l == r) {
        nodes[node].val = nodes[node_prev].val + val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[node].right = nodes[node_prev].right;
        update(nodes[node_prev].left, nodes[node].left, l, mid, ind, val);
    } else {
        nodes[node].right = idx;
        nodes[idx++] = Node();
        nodes[node].left = nodes[node_prev].left;
        update(nodes[node_prev].right, nodes[node].right, mid + 1, r, ind, val);
    }
    nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
    return;
}

int trav(int node_u, int node_v, int node_lca, int l, int r) {
    if (l == r) {
        if (nodes[node_u].val + nodes[node_v].val - 2 * nodes[node_lca].val == 0) {
            return l;
        } else {
            return -1;
        }
    }
    int mid = (l + r) / 2;
    int ct = nodes[nodes[node_u].right].val + nodes[nodes[node_v].right].val - 2 * nodes[nodes[node_lca].right].val;
    if (ct < r - mid) {
        return trav(nodes[node_u].right, nodes[node_v].right, nodes[node_lca].right, mid + 1, r);
    } else {
        return trav(nodes[node_u].left, nodes[node_v].left, nodes[node_lca].left, l, mid);
    }
}

int vis[N];
int tin[N];
int tout[N];
int up[K][N];
int timer = 0;

void dfs(int u, int p, int n) {
    vis[u] = 1;
    ct++;
    tin[u] = timer++;
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    for (auto [v, wt] : adj[u]) {
        if (!vis[v]) {
            root[v] = idx;
            nodes[idx++] = Node();
            update(root[u], root[v], 0, n - 2, wt, 1);
            dfs(v, u, n);
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

int main() {
	IOS;
	int t;
	cin >> t;
	while (t--) {
        int n, m;
        cin >> n >> m;
        vector<tuple<int, int, int>> edges;
        for (int i = 0; i < m; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            edges.push_back(make_tuple(wt, u, v));
        }
        sort(edges.begin(), edges.end());
        ll sum = 0;
        for (int i = 0; i < n - 1; i++) {
            auto [wt, u, v] = edges[i];
            val[i] = wt;
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});

            sum += wt;
        }
        idx = 0;
        root[0] = idx;
        nodes[idx++] = Node();
        build(0, 0, n - 2);
        dfs(0, 0, n);
        if (ct != n) {
            cout << sum << endl;
        } else {
            ll ans = INF;
            if (edges.size() > n) {
                ans = sum - get<0>(edges[n - 2]) - get<0>(edges[n - 3]) + get<0>(edges[n - 1]) + get<0>(edges[n]);
            }
            for (int i = n - 1; i < edges.size(); i++) {
                auto [wt, u, v] = edges[i];
                int l = lca(u, v);
                int j = trav(root[u], root[v], root[l], 0, n - 2);
                if (j != -1) {
                    ans = min(ans, sum - val[j] + wt);
                }
            }

            if (ans == INF) {
                cout << -1 << endl;
            } else {
                cout << ans << endl;
            }
        }
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            vis[i] = 0;
        }
        idx = 0;
        timer = 0;
        ct = 0;
	}


	return 0;
}
