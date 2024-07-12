//https://cses.fi/problemset/task/2143
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e4 + 5;

list<int> adj[N];
list<int> rev[N];
stack<int> s;

bool vis[N];
int parent[N];

set<int> scc[N];

bitset<N> b[N];

void fillStack(int v) {
    vis[v] = true;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            fillStack(*it);
        }
    }
    s.push(v);
}

void dfs(int v, int j) {
    vis[v] = true;
    parent[v] = j;
    for (auto it = rev[v].begin(); it != rev[v].end(); ++it) {
        if (!vis[*it]) {
            dfs(*it, j);
        }
    }
}

void dfs_scc(int u) {
    vis[u] = true;
    for (int v : scc[u]) {
        if (!vis[v]) {
            dfs_scc(v);
        }
        b[u] |= b[v];
    }
}

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        rev[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            fillStack(i);
        }
    }
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
    }
    int j = 0;
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        if (vis[v] == false) {
            dfs(v, j);
            j++;
        }
    }
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            if (parent[u] != parent[v]) {
                scc[parent[u]].insert(parent[v]);
            }
        }
        vis[u] = false;
    }
    for (int i = 0; i < j; i++) {
        b[i].set(i);
    }
    for (int i = 0; i < j; i++) {
        if (!vis[i]) {
            dfs_scc(i);
        }
    }
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (b[parent[u]][parent[v]]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }


    return 0;
}
