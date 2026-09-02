//https://codeforces.com/contest/1423/problem/H
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int parent[N];
int sz[N];
int ans[N];
int first[N];

vector<pair<int, int>> segtree[4 * N];
vector<pair<int, int>> ask[N];
vector<tuple<int, int, int, int>> restore;

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
            ct++;
        }
    }
    if (l == r) {
        for (auto [i, u] : ask[l]) {
            int x = dsu_find(u);
            ans[i] = sz[x];
        }
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
    }
    return;
}

int main() {
    IOS;
    int n, q, k;
    cin >> n >> q >> k;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i <= q; i++) {
        first[i] = q + 1;
    }
    vector<tuple<int, int, int>> query;
    int d = 0, m = 0;

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            query.push_back({t, u, v});
        } else if (t == 2) {
            int u;
            cin >> u;
            u--;
            query.push_back({t, -1, u});
        } else {
            query.push_back({t, -1, -1});
            d++;
            first[d] = i;
        }
    }
    d = 0;
    for (int i = 0; i < q; i++) {
        int t = get<0>(query[i]);
        if (t == 1) {
            auto [_, u, v] = query[i];
            upd(0, q, i, (d + k >= q ? q : first[d + k] - 1), make_pair(u, v), 0);
        } else if (t == 2) {
            auto [_, __, u] = query[i];
            ask[i].push_back({m++, u});
        } else {
            d++;
        }
    }

    dfs(0, q, 0);
    for (int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
