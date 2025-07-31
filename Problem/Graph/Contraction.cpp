//https://atcoder.jp/contests/abc411/tasks/abc411_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

set<int> adj[N];
set<pair<int, int>> st;
int parent[N];

int e = 0;

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (adj[a].size() > adj[b].size()) {
        swap(a, b);
    }
    e -= (int)adj[a].size();
    e -= (int)adj[b].size();
    adj[b].erase(a);
    adj[a].erase(b);
    e++;
    for (int v : adj[a]) {
        adj[v].erase(a);
        adj[v].insert(b);
        adj[b].insert(v);
    }
    e += (int)adj[b].size();
    parent[a] = b;
}


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].insert(v);
        adj[v].insert(u);
        edges.push_back({u, v});
        e++;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int j;
        cin >> j;
        j--;
        auto [u, v] = edges[j];
        u = dsu_find(u), v = dsu_find(v);
        if (u != v) {
            dsu_unite(u, v);
        }
        cout << e << endl;
    }
    return 0;
}
