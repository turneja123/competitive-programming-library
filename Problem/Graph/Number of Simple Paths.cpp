//https://codeforces.com/contest/1454/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

vector<int> adj[N];
int parent[N];
int color[N];
int cycle[N];
int sz[N];
vector<int> cyc;

void dfs(int u, int p) {
    color[u] = 1;
    parent[u] = p;
    for (int v : adj[u]) {
        if (color[v] == 0) {
            dfs(v, u);
        } else if (color[v] == 1 && v != p) {
            int x = u;
            while (x != v) {
                cyc.push_back(x);
                x = parent[x];
            }
            cyc.push_back(v);
            for (int i = 0; i < cyc.size(); i++) {
                int x = cyc[i];
                cycle[x] = true;
            }
        }
        if (cyc.size()) {
            color[u] = 2;
            return;
        }
    }
    color[u] = 2;
    return;
}

void dfs_tree(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (!cycle[v] && v != p) {
            dfs_tree(v, u);
            sz[u] += sz[v];
        }
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
        for (int i = 0; i < n; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, 0);
        long long ans = 0;
        int m = cyc.size();
        for (int u : cyc) {
            dfs_tree(u, u);
            ans += (long long)sz[u] * (sz[u] - 1) + (long long)2 * sz[u] * (n - sz[u]);
        }
        ans /= 2;
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            cycle[i] = false;
            color[i] = 0;
            sz[i] = 0;
            parent[i] = 0;
        }
        cyc.clear();
    }
    return 0;
}

