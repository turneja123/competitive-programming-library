//https://judge.yosupo.jp/problem/scc
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

vector<int> adj[N];
vector<int> rev[N];
stack<int> s;

int a[N];
bool vis[N];
int parent[N];
int deg[N];
set<int> scc[N];
vector<int> comp[N];

void fillStack(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            fillStack(v);
        }
    }
    s.push(u);
}

void dfs(int u, int j) {
    vis[u] = true;
    parent[u] = j;
    comp[j].push_back(u);
    for (int v : rev[u]) {
        if (!vis[v]) {
            dfs(v, j);
        }
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
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
            dfs(v, j++);
        }
    }
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            if (parent[u] != parent[v]) {
                auto it = scc[parent[u]].find(parent[v]);
                if (it == scc[parent[u]].end()) {
                    scc[parent[u]].insert(parent[v]);
                    deg[parent[v]]++;
                }
            }
        }
    }
    queue<int> q;
    for (int i = 0; i < j; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }
    vector<int> comps;
    while (q.size()) {
        int u = q.front();
        q.pop();
        comps.push_back(u);
        for (int v : scc[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }
    cout << j << endl;
    for (int x : comps) {
        cout << comp[x].size() << " ";
        for (int y : comp[x]) {
            cout << y << " ";
        }
        cout << endl;
    }


    return 0;
}
