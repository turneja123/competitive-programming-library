//https://judge.yosupo.jp/problem/jump_on_tree
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int K = 21;

vector<int> adj[N];
int up[K][N];
int depth[N];

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

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    for (int i = 0; i < q; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        int l = lca(u, v);
        if (x > depth[u] + depth[v] - 2 * depth[l]) {
            cout << -1 << endl;
            continue;
        }
        if (x <= depth[u] - depth[l]) {
            for (int k = 20; k >= 0; k--) {
                int c = x & (1 << k);
                if (c) {
                    u = up[k][u];
                }
            }
            cout << u << endl;
        } else {
            x = depth[u] + depth[v] - 2 * depth[l] - x;
            for (int k = 20; k >= 0; k--) {
                int c = x & (1 << k);
                if (c) {
                    v = up[k][v];
                }
            }
            cout << v << endl;
        }
    }


    return 0;
}
