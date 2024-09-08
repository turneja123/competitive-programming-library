//https://www.spoj.com/problems/DISQUERY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 19;

vector<pair<int, int>> adj[N];
int a[N];
pair<int, pair<int, int>> up[K][N];
int depth[N];

int mn, mx;

void dfs(int u, int p) {
    up[0][u].first = p;
    up[0][u].second = make_pair(min(a[p], a[u]), max(a[p], a[u]));
    for (int k = 1; k < K; k++) {
        up[k][u].first = up[k - 1][up[k - 1][u].first].first;
        up[k][u].second.first = min(up[k - 1][u].second.first, up[k - 1][up[k - 1][u].first].second.first);
        up[k][u].second.second = max(up[k - 1][u].second.second, up[k - 1][up[k - 1][u].first].second.second);
    }
    for (pair<int, int> pr : adj[u]) {
        int v = pr.first, wt = pr.second;
        if (v != p) {
            a[v] = wt;
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
        mn = min(mn, a[u]), mx = max(mx, a[u]);
        return;
    }
    for (int k = K - 1; k >= 0; k--) {
        int c = x & (1 << k);
        if (c) {
            mn = min(mn, up[k][u].second.first), mx = max(mx, up[k][u].second.second);
            u = up[k][u].first;
        }
    }
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
    }
    dfs(0, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int l = lca(u, v);
        mn = 1e9, mx = 0;
        if (u != l) {
            int d = depth[u] - depth[l] - 1;
            calc(u, d);
        }
        if (v != l) {
            int d = depth[v] - depth[l] - 1;
            calc(v, d);
        }
        cout << mn << " " << mx << endl;
    }
    return 0;
}
