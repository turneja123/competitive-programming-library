//https://cses.fi/problemset/task/2080/
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
int freqs[N];
vector<int> adj[N];

long long ans = 0;

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

int dfs_depth1(int u, int p, int k) {
    int low = depth[u];
    if (depth[u] == k) {
        ans++;
    }
    if (k - depth[u] >= 0) {
        ans += freqs[k - depth[u]];
    } else {
        return low;
    }

    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + 1;
            low = max(low, dfs_depth1(v, u, k));
        }
    }
    return low;
}

void dfs_depth2(int u, int p, int k) {
    if (depth[u] > k) {
        return;
    }
    freqs[depth[u]]++;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_depth2(v, u, k);
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

    int mx = 0;
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = 1;
            int m = dfs_depth1(v, v, k);
            mx = max(mx, m);
            dfs_depth2(v, v, k);
        }
    }
    for (int i = 0; i <= mx; i++) {
        freqs[i] = 0;
    }
    for (int v : adj[c]) {
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
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build(0, -1, k);
    cout << ans;


    return 0;
}
