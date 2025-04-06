//https://judge.yosupo.jp/problem/persistent_unionfind
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int parent[N];
int sz[N];
int ans[N];


vector<int> adj[N];
pair<int, int> node[N];
vector<tuple<int, int, int, int>> restore;
vector<tuple<int, int, int>> queries[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

void dfs(int u, int p) {
    int f = 0;
    if (u != 0) {
        auto [a, b] = node[u];
        int x = dsu_find(a), y = dsu_find(b);
        if (x != y) {
            restore.push_back(make_tuple(x, sz[x], y, sz[y]));
            dsu_unite(x, y);
            f = 1;
        }
    }
    for (auto [a, b, ind] : queries[u]) {
        int x = dsu_find(a), y = dsu_find(b);
        if (x != y) {
            ans[ind] = 0;
        } else {
            ans[ind] = 1;
        }
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    if (f) {
        auto [u, su, v, sv] = restore.back();
        parent[u] = u;
        parent[v] = v;
        sz[u] = su;
        sz[v] = sv;
        restore.pop_back();
    }
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    int j = 0;
    for (int i = 1; i <= q; i++) {
        int t, k, u, v;
        cin >> t >> k >> u >> v;
        k++;
        if (t == 0) {
            adj[k].push_back(i);
            adj[i].push_back(k);
            node[i] = make_pair(u, v);
        } else {
            queries[k].push_back(make_tuple(u, v, j++));
        }
    }
    dfs(0, 0);
    for (int i = 0; i < j; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
