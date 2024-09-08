//https://codeforces.com/contest/208/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int K = 21;

vector<int> root;
vector<int> adj[N];
int up[K][N];
int depth[N];
int ans[N];
int parent[N];

vector<pair<int, int>> queries[N];
map<int, int> mp[N];

void dfs(int u, int p) {
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
    return;
}

int lca(int u, int v) {
    if (depth[v] > depth[u]) {
        swap(u, v);
    }
    int x = depth[u] - depth[v];
    for (int k = 20; k >= 0; k--) {
        int c = x & (1 << k);
        if (c) {
            u = up[k][u];
        }
    }
    if (u == v) {
        return u;
    }
    for (int k = 20; k >= 0; k--) {
        if (up[k][u] != up[k][v]) {
            u = up[k][u], v = up[k][v];
        }
    }
    return up[0][u];
}

int kth(int u, int x) {
    for (int k = 20; k >= 0; k--) {
        int c = x & (1 << k);
        if (c) {
            u = up[k][u];
        }
    }
    return u;
}

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (mp[a].size() > mp[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        mp[b][it->first] += it->second;
    }
    return;
}

void dfs_calc(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs_calc(v, u);
        }
    }
    mp[u][depth[u]]++;
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b);
        }
    }
    int a = dsu_find(u);
    for (int i = 0; i < queries[u].size(); i++) {
        ans[queries[u][i].second] = mp[a][queries[u][i].first + depth[u]] - 1;
    }

    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        if (p == 0) {
            root.push_back(i);
        } else {
            p--;
            adj[i].push_back(p);
            adj[p].push_back(i);
        }
        parent[i] = i;
    }
    for (int i : root) {
        dfs(i, i);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, k;
        cin >> u >> k;
        u--;
        if (depth[u] < k) {
            ans[i] = 0;
        } else {
            int l = kth(u, k);
            queries[l].push_back(make_pair(k, i));
        }
    }
    for (int i : root) {
        dfs_calc(i, i);
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << " ";
    }


    return 0;
}
