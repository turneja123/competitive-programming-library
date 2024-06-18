//https://codeforces.com/contest/375/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

vector<int> adj[N];
vector<pair<int, int>> queries[N];

map<int, int> mp[N];
tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> t[N];

int ans[N];
int sz[N];
int parent[N];
int vals[N];

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (mp[a].size() > mp[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        auto f = mp[b].find(it->first);
        if (f == mp[b].end()) {
            mp[b][it->first] = it->second;
            t[b].insert(make_pair(it->second, it->first));
        } else {
            t[b].erase(t[b].find(make_pair(f->second, it->first)));
            f->second += it->second;
            t[b].insert(make_pair(f->second, it->first));
        }
    }
    return;
}

void dfs(int u, int p) {
    mp[u][vals[u]] = 1;
    t[u].insert(make_pair(1, vals[u]));
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }

    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b);
        }
    }
    int a = dsu_find(u);
    for (int i = 0; i < queries[u].size(); i++) {
        int k = queries[u][i].first;
        int x = t[a].size() - t[a].order_of_key(make_pair(k, -1));
        ans[queries[u][i].second] = x;
    }
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
        parent[i] = i;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < q; i++) {
        int u, x;
        cin >> u >> x;
        u--;
        queries[u].push_back(make_pair(x, i));
    }
    dfs(0, -1);
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
