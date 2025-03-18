//https://dmoj.ca/problem/ioi11p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int sz[N];
bool seen_c[N];
int parent_c[N];
int depth[N];
long long path[N];
vector<pair<int, int>> adj[N];
map<long long, int> mp;

int ans = N;

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v] && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

void dfs1(int u, int p, int k) {
    if (path[u] <= k) {
        auto it = mp.find(k - path[u]);
        if (it != mp.end()) {
            ans = min(ans, depth[u] + it->second);
        }
    }
    if (path[u] == k) {
        ans = min(ans, depth[u]);
    }
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            path[v] = path[u] + wt;
            depth[v] = depth[u] + 1;
            dfs1(v, u, k);
        }
    }
    return;
}

void dfs2(int u, int p, int k) {
    auto it = mp.find(path[u]);
    if (it == mp.end()) {
        mp[path[u]] = depth[u];
    } else {
        mp[path[u]] = min(mp[path[u]], depth[u]);
    }
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs2(v, u, k);
        }
    }
    return;
}


void build(int u, int p, int k) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;

    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = 1;
            path[v] = wt;
            dfs1(v, v, k);
            dfs2(v, v, k);
        }
    }
    mp.clear();
    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            build(v, c, k);
        }
    }
    return;
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
    }
    build(0, -1, k);
    if (ans == N) {
        ans = -1;
    }
    cout << ans;


    return 0;
}
