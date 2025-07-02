//https://ocpc2025s.eolymp.space/en/compete/ejd99p3q1p1tnem8befqm7318o/problem/5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

int sz[N];
bool seen_c[N];
int parent_c[N];
int depth[N];
int sz_c[N];
vector<int> adj[N];
vector<tuple<int, int, int>> ans;

int idx = 0;

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


void dfs_depth(int u, int p) {
    sz_c[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + 1;
            dfs_depth(v, u);
            sz_c[u] += sz_c[v];
        }
    }
    return;
}

void dfs_depth2(int u, int p) {
    ans.push_back({depth[u], idx, u});
    idx++;
    vector<pair<int, int>> szs;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            szs.push_back({-sz_c[v], v});
        }
    }
    sort(szs.begin(), szs.end());
    for (auto [s, v] : szs) {
        dfs_depth2(v, u);
    }


}


void build(int u, int p) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;
    ans.push_back({0, 0, c});
    vector<pair<int, int>> szs;
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = 1;
            dfs_depth(v, v);
            szs.push_back({-sz_c[v], v});
        }
    }
    sort(szs.begin(), szs.end());
    for (auto [s, v] : szs) {
        dfs_depth2(v, c);
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        build(0, -1);
        cout << "YES" << endl;
        sort(ans.begin(), ans.end());
        for (auto [_, __, u] : ans) {
            cout << u + 1 << " ";
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            seen_c[i] = 0;
            depth[i] = 0;
            parent_c[i] = 0;
            sz_c[i] = 0;
            sz[i] = 0;
        }
        ans.clear();
        idx = 0;

    }


    return 0;
}
