//https://www.spoj.com/problems/QTREE5/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 1e9;

int sz[N];
bool seen_c[N];
int parent_c[N];
int depth[N];
int color[N];
int depth_cen[N];


multiset<int> ans[N];
vector<int> adj[N];
vector<int> id[N];
vector<int> dist[N];

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (int v : adj[u]) {
        if (v != p && !seen_c[v] && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

void dfs_depth(int u, int p, int c) {
    id[u].push_back(dist[c].size());
    dist[c].push_back(depth[u]);
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + 1;
            dfs_depth(v, u, c);
        }
    }
    return;
}

void build(int u, int p, int d) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    depth_cen[c] = d;
    parent_c[c] = p;
    seen_c[c] = true;

    id[c].push_back(0);
    dist[c].push_back(0);
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = 1;
            dfs_depth(v, v, c);
        }
    }
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            build(v, c, d + 1);
        }
    }
    return;
}

void upd(int u, int f) {
    int c = u, de = depth_cen[u];
    while (1) {
        int d = dist[c][id[u][de]];
        if (f == 1) {
            ans[c].insert(d);
        } else {
            ans[c].erase(ans[c].find(d));
        }
        if (c == parent_c[c]) {
            break;
        }
        c = parent_c[c];
        de--;
    }
    return;
}

int query(int u) {
    int best = INF;
    int c = u, de = depth_cen[u];
    while (1) {
        int d = dist[c][id[u][de]];
        if (ans[c].size()) {
            best = min(best, d + *ans[c].begin());
        }
        if (c == parent_c[c]) {
            break;
        }
        c = parent_c[c];
        de--;
    }
    return best;
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build(0, -1, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t, u;
        cin >> t >> u;
        u--;
        if (t == 0) {
            color[u] ^= 1;
            upd(u, color[u]);
        } else {
            int ans = query(u);
            if (ans == INF) {
                ans = -1;
            }
            cout << ans << endl;
        }
    }

    return 0;
}
