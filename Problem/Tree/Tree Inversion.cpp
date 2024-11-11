//https://atcoder.jp/contests/abc337/tasks/abc337_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> st[N];

int inv[N];
int contribution[N];
int sz[N];
int parent[N];
long long subtree[N];
long long dp[N];

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

void dfs_subtree(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs_subtree(v, u);
            subtree[u] += subtree[v];
        }
    }
    st[u].insert(u);
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            contribution[v] = st[b].order_of_key(u);
            inv[u] += contribution[v];
            dsu_merge(a, b);
        }
    }
    subtree[u] += inv[u];
    return;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dp[v] = dp[u] + v - inv[v] + subtree[u] - subtree[v] - contribution[v];
            dfs(v, u);
        }
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    dfs_subtree(0, 0);
    dfs(0, 0);
    for (int i = 0; i < n; i++) {
        cout << subtree[i] + dp[i] << " ";
    }

    return 0;
}

