//https://codeforces.com/contest/1706/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int K = 20;

int parent[N];
int tin[N];
int tout[N];
int up[K][N];
int timer = 0;

vector<int> adj[N];

int dsu_find(int u) {
    if (parent[u] == u) {
        return u;
    }
    return parent[u] = dsu_find(parent[u]);
}

void add_edge(int u, int v, int e) {
    u = dsu_find(u), v = dsu_find(v);
    if (u == v) {
        return;
    }
    parent[u] = e;
    parent[v] = e;
    parent[e] = e;
    adj[e].push_back(v);
    adj[e].push_back(u);
    adj[u].push_back(e);
    adj[v].push_back(e);
    return;
}

void dfs(int u, int p) {
    tin[u] = timer++;
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    tout[u] = timer++;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int k = K - 1; k >= 0; k--) {
        if (!is_ancestor(up[k][u], v)) {
            u = up[k][u];
        }
    }
    return up[0][u];
}

int table_mn[K][N];
int table_mx[K][N];
int mn[K][N];
int mx[K][N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table_mn[0][i] = tin[i - 1];
        table_mx[0][i] = tin[i - 1];
        mn[0][i] = i - 1;
        mx[0][i] = i - 1;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table_mn[k - 1][i] < table_mn[k - 1][i + (1 << (k - 1))]) {
                table_mn[k][i] = table_mn[k - 1][i];
                mn[k][i] = mn[k - 1][i];
            } else {
                table_mn[k][i] = table_mn[k - 1][i + (1 << (k - 1))];
                mn[k][i] = mn[k - 1][i + (1 << (k - 1))];
            }

            if (table_mx[k - 1][i] > table_mx[k - 1][i + (1 << (k - 1))]) {
                table_mx[k][i] = table_mx[k - 1][i];
                mx[k][i] = mx[k - 1][i];
            } else {
                table_mx[k][i] = table_mx[k - 1][i + (1 << (k - 1))];
                mx[k][i] = mx[k - 1][i + (1 << (k - 1))];
            }
        }
    }
    return;
}

pair<int, int> query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    int a, b;
    if (table_mn[k][l] < table_mn[k][r - (1 << k) + 1]) {
        a = mn[k][l];
    } else {
        a = mn[k][r - (1 << k) + 1];
    }

    if (table_mx[k][l] > table_mx[k][r - (1 << k) + 1]) {
        b = mx[k][l];
    } else {
        b = mx[k][r - (1 << k) + 1];
    }

    return {a, b};
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        int e = n;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            add_edge(u, v, e);
            e++;
        }
        int root = dsu_find(0);
        dfs(root, root);
        build(n);
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            if (l == r) {
                cout << 0 << " ";
                continue;
            }
            auto [u, v] = query(l, r);
            cout << lca(u, v) - n + 1 << " ";
        }
        cout << endl;
        for (int i = 0; i < e; i++) {
            adj[i].clear();
        }
        timer = 0;
    }
    return 0;
}
