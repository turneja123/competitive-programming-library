//https://atcoder.jp/contests/abc368/tasks/abc368_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
vector<int> tin, tout;
vector<vector<int>> up;
int timer = 0, lg;

int depth[N];

int subgraph[N];
bool vis[N];

void dfs(int v, int p) {
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : adj[v]) {
        if (u != p) {
            dfs(u, v);
        }
    }
    tout[v] = timer++;
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
    for (int i = lg; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    lg = ceil(log2(n));
    up.assign(n, vector<int>(lg + 1));
    tin.resize(n);
    tout.resize(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        v--; u--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    for (int i = 0; i < k; i++) {
        cin >> subgraph[i];
        subgraph[i]--;
    }
    int root = subgraph[0];
    for (int i = 1; i < k; i++) {
        root = lca(root, subgraph[i]);
    }
    int ans = 0;

    for (int i = 0; i < k; i++) {
        int u = subgraph[i];
        while (!vis[u]) {
            ans++;
            vis[u] = true;
            if (u == root) {
                break;
            }
            u = up[u][0];
        }
    }
    cout << ans;

    return 0;
}
