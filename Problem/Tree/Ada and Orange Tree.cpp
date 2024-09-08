//https://www.spoj.com/problems/ADAORANG/
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
int a[N];
bitset<250> b[N];

void dfs(int u, int p) {
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    b[u].set(a[u]);
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            b[u] |= b[v];
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
    int t;
    cin >> t;
    while (t--) {
        int n, q, root;
        cin >> n >> q >> root;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        depth[root] = 0;
        dfs(root, root);
        for (int i = 0; i < q; i++) {
            int u, v;
            cin >> u >> v;
            int l = lca(u, v);
            cout << b[l].count() << endl;
        }
        for (int i = 0; i < n; i++) {
            b[i].reset();
            adj[i].clear();
        }

    }


    return 0;
}
