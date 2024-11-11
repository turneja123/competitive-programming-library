//https://cses.fi/problemset/task/2101/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 200005;
const int K = 19;

int parent[N];
int sz[N];
bool vis[N];
bool vis_mst[N];

vector<int> adj[N];
vector<pair<int, int>> mst[N];
tuple<int, int, int> edge[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    a = dsu_find(a);
    b = dsu_find(b);
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

void dfs(int v) {
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            vis[*it] = true;
            dfs(*it);
        }
    }
}

int a[N];
pair<int, int> up[K][N];
int depth[N];

int mx;

void dfs_mst(int u, int p) {
    vis_mst[u] = true;
    up[0][u].first = p;
    up[0][u].second = max(a[p], a[u]);
    for (int k = 1; k < K; k++) {
        up[k][u].first = up[k - 1][up[k - 1][u].first].first;
        up[k][u].second = max(up[k - 1][u].second, up[k - 1][up[k - 1][u].first].second);
    }
    for (pair<int, int> pr : mst[u]) {
        int v = pr.first, wt = pr.second;
        if (v != p) {
            a[v] = wt;
            depth[v] = depth[u] + 1;
            dfs_mst(v, u);
        }
    }
    return;
}

int lca(int u, int v) {
    if (depth[v] > depth[u]) {
        swap(u, v);
    }
    int x = depth[u] - depth[v];
    for (int k = K - 1; k >= 0; k--) {
        int c = x & (1 << k);
        if (c) {
            u = up[k][u].first;
        }
    }
    if (u == v) {
        return u;
    }
    for (int k = K - 1; k >= 0; k--) {
        if (up[k][u].first != up[k][v].first) {
            u = up[k][u].first, v = up[k][v].first;
        }
    }
    return up[0][u].first;
}

void calc(int u, int x) {
    if (x == 0) {
        mx = max(mx, a[u]);
        return;
    }
    for (int k = K - 1; k >= 0; k--) {
        int c = x & (1 << k);
        if (c) {
            mx = max(mx, up[k][u].second);
            u = up[k][u].first;
        }
    }
    return;
}

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int a, b, wt;
        cin >> a >> b;
        wt = i + 1;
        a--, b--;
        edge[i] = make_tuple(wt, a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
        if (!vis[i]) {
            vis[i] = true;
            dfs(i);
        }
    }
    sort(edge, edge + m);
    for (int i = 0; i < m; i++) {
        int wt = get<0>(edge[i]);
        int a = get<1>(edge[i]);
        int b = get<2>(edge[i]);
        int p1 = dsu_find(a);
        int p2 = dsu_find(b);
        if (p1 != p2) {
            dsu_unite(p1, p2);
            mst[a].push_back(make_pair(b, wt));
            mst[b].push_back(make_pair(a, wt));
        }
    }
    for (int i = 0; i < n; i++) {
        if (!vis_mst[i]) {
            dfs_mst(i, i);
        }
    }
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int a = dsu_find(u), b = dsu_find(v);
        if (a != b) {
            cout << -1 << endl;
            continue;
        }
        int l = lca(u, v);
        mx = 0;
        if (u != l) {
            int d = depth[u] - depth[l] - 1;
            calc(u, d);
        }
        if (v != l) {
            int d = depth[v] - depth[l] - 1;
            calc(v, d);
        }
        cout << mx << endl;
    }

    return 0;
}
