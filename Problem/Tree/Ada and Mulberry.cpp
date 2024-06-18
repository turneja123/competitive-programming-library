//https://www.spoj.com/problems/ADABERRY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

list <int> adj[N];

int sz[N];
int tour[N];
int vals[N];
int parent[N];
int a[N];
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> segtree[4 * N];
bool vis[N];

int euler = 0;

int dfs(int v, int ct) {
    tour[v] = euler++;
    vis[v] = true;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            parent[*it] = v;
            ct += dfs(*it, 1);
        }
    }
    return sz[v] = ct;
}

int query(int l, int r, int lq, int rq, int val, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node].order_of_key(val);
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, val, 2 * node + 1) + query(mid + 1, r, lq, rq, val, 2 * node + 2);
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node].insert(val);
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node].insert(val);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        if (a[l] != -1) {
            segtree[node].insert(a[l]);
        }
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    for (int x : segtree[2 * node + 1]) {
        segtree[node].insert(x);
    }
    for (int x : segtree[2 * node + 2]) {
        segtree[node].insert(x);
    }
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int m = n;
    for (int i = 0; i < q; i++) {
        int u, x;
        cin >> u >> x;
        adj[u].push_back(m);
        adj[m].push_back(u);
        vals[m] = x;
        m++;
    }
    dfs(0, 1);
    for (int i = 0; i < n; i++) {
        a[tour[i]] = vals[i];
    }
    for (int i = n; i < m; i++) {
        a[tour[i]] = -1;
    }
    build(0, m - 1, 0);
    for (int i = n; i < m; i++) {
        update(0, m - 1, tour[i], vals[i], 0);
        int u = parent[i];
        int ans = query(0, m - 1, tour[u], tour[u] + sz[u] - 1, vals[i], 0);
        cout << ans << endl;

    }
    return 0;
}
