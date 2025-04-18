//https://cses.fi/problemset/task/2133/
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

vector<pair<int, int>> segtree[4 * N];
vector<tuple<int, int, int, int>> restore;
int comps;

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

void upd(int l, int r, int lq, int rq, pair<int, int> edge, int node) {
    if (r < lq || l > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].push_back(edge);
        return;
    }
    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, edge, 2 * node + 1);
    upd(mid + 1, r, lq, rq, edge, 2 * node + 2);
    return;
}

void dfs(int l, int r, int node) {
    int ct = 0;

    for (auto [u, v] : segtree[node]) {
        int x = dsu_find(u), y = dsu_find(v);
        if (x != y) {
            restore.push_back(make_tuple(x, sz[x], y, sz[y]));
            dsu_unite(x, y);
            comps--;
            ct++;
        }
    }
    if (l == r) {
        ans[l] = comps;
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }
    for (int i = 0; i < ct; i++) {
        auto [u, su, v, sv] = restore.back();
        parent[u] = u;
        parent[v] = v;
        sz[u] = su;
        sz[v] = sv;
        restore.pop_back();
        comps++;
    }
    return;
}

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    comps = n;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    map<pair<int, int>, int> mp;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u > v) {
            swap(u, v);
        }
        mp[{u, v}] = 0;
    }
    vector<tuple<int, int, int, int>> edges;
    for (int i = 1; i <= q; i++) {
        int t, u, v;
        cin >> t >> u >> v;
        u--, v--;
        if (u > v) {
            swap(u, v);
        }
        if (t == 1) {
            mp[{u, v}] = i;
        } else {
            auto it = mp.find(make_pair(u, v));
            edges.push_back(make_tuple(u, v, it->second, i - 1));
            mp.erase(it);
        }
    }
    while (mp.size()) {
        auto [u, v] = mp.begin()->first;
        edges.push_back(make_tuple(u, v, mp.begin()->second, q));
        mp.erase(mp.begin());
    }
    for (auto [u, v, l, r] : edges) {
        upd(0, q, l, r, {u, v}, 0);
    }
    dfs(0, q, 0);
    for (int i = 0; i <= q; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
