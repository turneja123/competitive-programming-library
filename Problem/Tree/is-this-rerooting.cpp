//https://codeforces.com/group/qepOKX6Mi9/contest/363472/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 19;

vector<int> adj[N];

int up[K][N];

int depth[N];
int sz[N];

void dfs(int u, int p) {
    sz[u] = 1;
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        int v = up[k - 1][u];
        up[k][u] = up[k - 1][v];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
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
            u = up[k][u];
        }
    }
    if (u == v) {
        return u;
    }
    for (int k = K - 1; k >= 0; k--) {
        if (up[k][u] != up[k][v]) {
            u = up[k][u], v = up[k][v];
        }
    }
    return up[0][u];
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u == v) {
            cout << n << endl;
            continue;
        }
        int l = lca(u, v);
        if (l != v) {
            cout << sz[v] << endl;
        } else {
            int d = depth[u] - depth[v] - 1;
            for (int k = K - 1; k >= 0; k--) {
                int c = d & (1 << k);
                if (c) {
                    u = up[k][u];
                }
            }
            cout << n - sz[u] << endl;
        }
    }
    return 0;
}

