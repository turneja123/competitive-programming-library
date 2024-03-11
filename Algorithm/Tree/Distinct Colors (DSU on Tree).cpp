//https://cses.fi/problemset/task/1139/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int ans[N];
int sz[N];
int parent[N];
vector<int> adj[N];
set<int> st[N];

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (st[a].size() > st[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = st[a].begin(); it != st[a].end(); ++it) {
        st[b].insert(*it);
    }
    return;
}

void dfs(int u, int p) {
    vector<int> child;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            child.push_back(v);
        }
    }
    for (int v : child) {
        int a = dsu_find(u), b = dsu_find(v);
        if (a != b) {
            dsu_merge(a, b);
        }
    }
    ans[u] = st[dsu_find(u)].size();
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        st[i].insert(a[i]);
    }
    dfs(0, -1);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
