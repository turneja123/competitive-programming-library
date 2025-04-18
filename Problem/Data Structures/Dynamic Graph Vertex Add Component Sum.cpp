//https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int parent[N];
int sz[N];
long long ans[N];
long long sum[N];

vector<pair<int, int>> segtree_edges[4 * N];
vector<pair<int, int>> segtree_values[4 * N];

vector<pair<int, int>> queries[N];
vector<tuple<int, int, long long, int, int, long long>> restore_edges;
vector<tuple<int, long long>> restore_values;

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
    sum[a] += sum[b];
    parent[b] = a;
}

void upd_edge(int l, int r, int lq, int rq, pair<int, int> edge, int node) {
    if (r < lq || l > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree_edges[node].push_back(edge);
        return;
    }
    int mid = (l + r) / 2;
    upd_edge(l, mid, lq, rq, edge, 2 * node + 1);
    upd_edge(mid + 1, r, lq, rq, edge, 2 * node + 2);
    return;
}

void upd_value(int l, int r, int lq, int rq, pair<int, int> val, int node) {
    if (r < lq || l > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree_values[node].push_back(val);
        return;
    }
    int mid = (l + r) / 2;
    upd_value(l, mid, lq, rq, val, 2 * node + 1);
    upd_value(mid + 1, r, lq, rq, val, 2 * node + 2);
    return;
}

void dfs(int l, int r, int node) {
    int ct_edges = 0, ct_values = 0;
    for (auto [u, v] : segtree_edges[node]) {
        int x = dsu_find(u), y = dsu_find(v);
        if (x != y) {
            restore_edges.push_back(make_tuple(x, sz[x], sum[x], y, sz[y], sum[y]));
            dsu_unite(x, y);
            ct_edges++;
        }
    }

    for (auto [u, x] : segtree_values[node]) {
        int y = dsu_find(u);
        restore_values.push_back(make_tuple(y, sum[y]));
        sum[y] += x;
        ct_values++;
    }
    if (l == r) {
        for (auto [u, i] : queries[l]) {
            int x = dsu_find(u);
            ans[i] = sum[x];
        }
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }

    for (int i = 0; i < ct_values; i++) {
        auto [u, x] = restore_values.back();
        sum[u] = x;
        restore_values.pop_back();
    }

    for (int i = 0; i < ct_edges; i++) {
        auto [u, su, smu, v, sv, smv] = restore_edges.back();
        parent[u] = u;
        parent[v] = v;
        sz[u] = su;
        sz[v] = sv;
        sum[u] = smu;
        sum[v]= smv;
        restore_edges.pop_back();
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
        cin >> sum[i];
    }
    map<pair<int, int>, int> mp;
    vector<tuple<int, int, int, int>> edges;
    int j = 0;
    for (int i = 1; i <= q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int u, v;
            cin >> u >> v;
            if (u > v) {
                swap(u, v);
            }
            mp[{u, v}] = i;
        } else if (t == 1) {
            int u, v;
            cin >> u >> v;
            if (u > v) {
                swap(u, v);
            }
            auto it = mp.find(make_pair(u, v));
            edges.push_back(make_tuple(u, v, it->second, i - 1));
            mp.erase(it);
        } else if (t == 2) {
            int u, x;
            cin >> u >> x;
            upd_value(0, q, i, q, {u, x}, 0);
        } else {
            int u;
            cin >> u;
            queries[i].push_back(make_pair(u, j++));
        }
    }
    while (mp.size()) {
        auto [u, v] = mp.begin()->first;
        edges.push_back(make_tuple(u, v, mp.begin()->second, q));
        mp.erase(mp.begin());
    }
    for (auto [u, v, l, r] : edges) {
        upd_edge(0, q, l, r, {u, v}, 0);
    }
    dfs(0, q, 0);
    for (int i = 0; i < j; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
