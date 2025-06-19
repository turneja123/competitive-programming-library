//https://www.spoj.com/problems/ADATOMEL/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int K = 19;
const int M = 1005;

int up[K][N];
int tin[N];
int tout[N];
int timer = 0;
vector<int> adj[N];
int vals[N];

bitset<M> table[K][N];

void dfs(int u, int p) {
    tin[u] = timer++;
    up[0][u] = p;
    table[0][u].set(vals[u]);
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
        table[k][u] = table[k - 1][u] | table[k - 1][up[k - 1][u]];
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

bitset<M> ans;

void calc(int a, int b) {
    for (int k = K - 1; k >= 0; k--) {
        if (tin[up[k][a]] >= tin[b]) {
            ans |= table[k][a];
            a = up[k][a];
        }
    }
    ans.set(vals[b]);
    return;
}

void calc_path(int u, int v) {
    int l = lca(u, v);
    calc(u, l);
    calc(v, l);
    return;
}

int main() {
    IOS;
    int n, k, q;
    cin >> n >> k >> q;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
        vals[i]--;
    }
    dfs(0, 0);
    for (int i = 0; i < q; i++) {
        int u, v;
        ans.reset();
        for (int j = 0; j < 3; j++) {
            cin >> u >> v;
            calc_path(u, v);
        }
        cout << ans.count() << endl;
    }
    return 0;
}
