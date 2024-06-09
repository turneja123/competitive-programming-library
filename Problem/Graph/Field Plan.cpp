//https://www.spoj.com/problems/FPLAN/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

list<int> adj[N];
list<int> rev[N];
stack<int> s;

bool vis[N];
int parent[N];
int sz[N];
int deg[N];
set<int> scc[N];
int ct = 0;

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
    sz[j]++;
    for (auto it = rev[v].begin(); it != rev[v].end(); ++it) {
        if (!vis[*it]) {
            dfs(*it, j);
        }
    }
}

void dfs_scc(int u) {
    vis[u] = true;
    ct += sz[u];
    for (int v : scc[u]) {
        if (!vis[v]) {
            dfs_scc(v);
        }
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
            adj[i].clear();
            rev[i].clear();
            scc[i].clear();
            vis[i] = false;
            deg[i] = 0;
            parent[i] = 0;
            sz[i] = 0;
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
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
                    deg[parent[v]]++;
                }
            }
        }
        vector<int> start;
        for (int i = 0; i < j; i++) {
            if (deg[i] == 0) {
                start.push_back(i);
            }
        }
        if (start.size() != 1) {
            cout << "Confused" << endl << endl;
        } else {
            for (int i = 0; i < j; i++) {
                vis[i] = false;
            }
            ct = 0;
            dfs_scc(start[0]);
            if (ct != n) {
                cout << "Confused" << endl << endl;
            } else {
                for (int i = 0; i < n; i++) {
                    if (parent[i] == start[0]) {
                        cout << i << endl;
                    }
                }
                cout << endl;
            }
        }
    }
    return 0;
}
