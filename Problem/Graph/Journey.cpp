//https://codeforces.com/contest/2164/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;
const int INF = 1e9;

int parent[N];
int ct[N];
int deg[N];
int comp[N];
vector<int> adj[N];


int dsu_find(int u) {
    if (parent[u] == u) {
        return u;
    }
    return parent[u] = dsu_find(parent[u]);
}

ll ans = 0;

void add_edge(int u, int v, int e, int wt, int id) {
    u = dsu_find(u), v = dsu_find(v);
    if (u == v) {
        comp[u] = min(comp[u], wt);
        return;
    }
    parent[u] = e;
    parent[v] = e;
    parent[e] = e;
    comp[e] = wt;
    adj[e].push_back(v);
    adj[e].push_back(u);
    adj[u].push_back(e);
    adj[v].push_back(e);

    return;
}


void dfs(int u, int p, int n, int val) {
    val = min(val, comp[u]);
    int x = -1, y = -1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, n, val);
            if (x == -1) {
                x = ct[v];
            } else if (y == -1) {
                y = ct[v];
            }
        }
    }
    if (x != -1) {
        if (x % 2 == 1 && y % 2 == 1) {
            ans += val;
        }
        ct[u] = x ^ y;
    }
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            deg[i] = 0;
        }
        vector<tuple<int, int, int>> edges;
        ans = 0;
        for (int i = 0; i < m; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            edges.push_back(make_tuple(u, v, wt));
            deg[u]++;
            deg[v]++;
            ans += wt;
        }
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            if (deg[i] % 2 == 1) {
                ct[i] = 1;
            } else {
                ct[i] = 0;
            }
        }
        int e = n;
        for (auto [u, v, wt] : edges) {
            add_edge(u, v, e, wt, e - n);
            e++;
        }
        int root = dsu_find(0);
        dfs(root, root, n, INF);

        cout << ans << endl;
        for (int i = 0; i < e; i++) {
            adj[i].clear();
        }
    }
    return 0;
}
