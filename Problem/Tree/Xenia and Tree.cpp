//https://codeforces.com/contest/342/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

int sz[N];
bool seen_c[N];
int parent_c[N];
int depth[N];
int ans[N];

map<int, int> dist[N];
vector<int> adj[N];

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
    dist[c][u] = depth[u];
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + 1;
            dfs_depth(v, u, c);
        }
    }
    return;
}

void build(int u, int p) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;
    dist[c][c] = 0;
    ans[c] = INF;
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = 1;
            dfs_depth(v, v, c);
        }
    }
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            build(v, c);
        }
    }
    return;
}

void upd(int u) {
    int c = u;
    while (1) {
        ans[c] = min(ans[c], dist[c][u]);
        if (c == parent_c[c]) {
            break;
        }
        c = parent_c[c];
    }
    return;
}

int query(int u) {
    int best = INF;
    int c = u;
    while (1) {
        best = min(best, dist[c][u] + ans[c]);
        if (c == parent_c[c]) {
            break;
        }
        c = parent_c[c];
    }
    return best;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build(0, -1);
    upd(0);
    for (int i = 0; i < q; i++) {
        int t, u;
        cin >> t >> u;
        u--;
        if (t == 1) {
            upd(u);
        } else {
            cout << query(u) << endl;
        }
    }

    return 0;
}
