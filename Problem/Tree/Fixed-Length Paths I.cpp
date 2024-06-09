//https://cses.fi/problemset/task/2080
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

int parent[N];
int depth[N];
vector<int> adj[N];
map<int, int> mp[N];
long long ans = 0;
int k;

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b, int u) {
    if (mp[a].size() > mp[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        int x = it->first - depth[u];
        auto f = mp[b].find(k - x + depth[u]);
        if (f != mp[b].end()) {
            ans += (long long)it->second * f->second;
        }
    }
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        auto f = mp[b].find(it->first);
        if (f == mp[b].end()) {
            mp[b][it->first] = it->second;
        } else {
            mp[b][it->first] += it->second;
        }
    }
    return;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
    mp[u][depth[u]] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b, u);
        }
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    dfs(0, -1);
    cout << ans;
    return 0;
}
