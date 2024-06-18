//https://atcoder.jp/contests/abc294/tasks/abc294_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<pair<int, long long>> adj[N];
int sz[N];
int tour[N];
ll sums[N];
ll a[N];
bool vis[N];
int euler = 0;

ll segtree[4 * N];
ll lazy[4 * N];

vector<int> tin, tout;
vector<vector<int>> up;
int timer = 0, lg;

vector<vector<int>> edges;


int dfs(int v, int ct, int p) {
    tour[v] = euler++;
    vis[v] = true;
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[it->first]) {
            sums[it->first] = it->second + sums[v];
            ct += dfs(it->first, 1, v);
        }
    }
    tout[v] = ++timer;
    return sz[v] = ct;
}

void compose(int parent, int child) {
    lazy[child] += lazy[parent];
}

void apply(int node, int l, int r) {
    segtree[node] += (r - l + 1) * lazy[node];
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    lazy[node] = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
}

ll getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
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
    int n, q;
    cin >> n;

    lg = ceil(log2(n));
    up.assign(n, vector<int>(lg + 1));
    tin.resize(n);
    tout.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; long long wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
        vector<int> ve{u, v, wt};
        edges.push_back(ve);
    }
    dfs(0, 1, 0);
    for (int i = 0; i < n; i++) {
        a[tour[i]] = sums[i];
    }
    build(0, n - 1, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            ll e, x;
            cin >> e >> x;
            e--;
            int u = edges[e][0], v = edges[e][1];
            if (up[u][0] == v) {
                swap(u, v);
            }
            incUpdate(0, 0, n - 1, tour[v], tour[v] + sz[v] - 1,  x - edges[e][2]);
            edges[e][2] = x;
        } else {
            int u, v;
            cin >> u >> v;
            u--, v--;
            int l = lca(u, v);

            ll ans = getSum(0, n - 1, tour[u], tour[u], 0) + getSum(0, n - 1, tour[v], tour[v], 0) - getSum(0, n - 1, tour[l], tour[l], 0) * 2;
            cout << ans << endl;
        }
    }
    return 0;
}
