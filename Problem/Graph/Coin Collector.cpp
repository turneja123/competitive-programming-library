//https://cses.fi/problemset/task/1686/
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

int a[N];
bool vis[N];
int parent[N];
int deg[N];
long long sum[N];
long long dp[N];
set<int> scc[N];

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
    sum[j] += a[v];
    for (auto it = rev[v].begin(); it != rev[v].end(); ++it) {
        if (!vis[*it]) {
            dfs(*it, j);
        }
    }
}


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
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
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        if (vis[v] == false) {
            dfs(v, v);
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

    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0 && parent[i] == i) {
            q.push(i);
        }
    }
    vector<int> sorted;
    while (q.size()) {
        int u = q.top();
        q.pop();
        sorted.push_back(u);
        for (int v : scc[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (parent[i] == i) {
            dp[i] = sum[i];
            ans = max(ans, dp[i]);
        }
    }

    for (int u : sorted) {
        for (int v : scc[u]) {
            dp[v] = max(dp[v], dp[u] + sum[v]);
            ans = max(ans, dp[v]);
        }
    }
    cout << ans;


    return 0;
}
