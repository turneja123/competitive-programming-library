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

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

gp_hash_table<int, int, custom_hash> dist[N];
multiset<int> ans[N];
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

void upd(int u, int f) {
    int c = u;
    while (1) {
        if (f == 1) {
            ans[c].insert(dist[c][u]);
        } else {
            ans[c].erase(ans[c].find(dist[c][u]));
        }
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
        if (ans[c].size()) {
            best = min(best, dist[c][u] + *ans[c].begin());
        }
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
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build(0, -1);
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
