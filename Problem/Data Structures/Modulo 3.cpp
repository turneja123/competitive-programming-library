//https://codeforces.com/contest/2104/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int query[N];
int ans[N];
int g[N];
int val[N];

struct Group {
    int sz;
    int parent;
    int dist;
    int cyc;
    int cyc_len;
    Group() {
    }
    Group(int x) {
        parent = x;
        sz = 1;
        dist = 0;
        cyc = 0;
        cyc_len = 0;
    }
};

Group dsu[N];

vector<pair<int, int>> segtree[4 * N];
vector<tuple<int, Group, int, Group, int, int>> restore;
int n, cycles = 0, in_cycle = 0;


pair<int, int> dsu_find(int a) {
    if (dsu[a].parent == a) {
        return {a, 0};
    }
    pair<int, int> p = dsu_find(dsu[a].parent);
    return {p.first, p.second ^ dsu[a].dist};
}

void dsu_unite(int a, int b, int d) {
    if (dsu[b].sz > dsu[a].sz) {
        swap(a, b);
    }
    dsu[a].sz += dsu[b].sz;
    dsu[b].dist = d ^ 1;
    if (dsu[b].cyc) {
        dsu[a].cyc = dsu[b].cyc;
        dsu[a].cyc_len = dsu[b].cyc_len;
    }
    dsu[b].parent = a;
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
        auto [x, dx] = dsu_find(u);
        auto [y, dy] = dsu_find(v);
        restore.push_back(make_tuple(x, dsu[x], y, dsu[y], in_cycle, cycles));
        if (x != y) {
            dsu_unite(x, y, dx ^ dy);
        } else {
            if (dsu[y].cyc) {
                cycles -= 1;
                in_cycle -= dsu[y].cyc_len;
            }
            cycles += 1;
            in_cycle += dx ^ dy ^ 1;
            dsu[y].cyc = 1;
            dsu[y].cyc_len = dx ^ dy ^ 1;
        }
        ct++;
    }
    if (l == r) {
        if (query[l] % 3 == 0) {
            ans[l] = 0;
        } else if (query[l] % 3 == 1) {
            ans[l] = 1;
        } else {
            int k = (n + cycles + in_cycle) % 2;
            if (k == 1) {
                ans[l] = 2;
            } else {
                ans[l] = 1;
            }

        }
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }
    for (int i = 0; i < ct; i++) {
        auto [x, gx, y, gy, q, r] = restore.back();
        dsu[x] = gx;
        dsu[y] = gy;
        in_cycle = q;
        cycles = r;
        restore.pop_back();
    }
    return;
}

int main() {
    IOS;
    int q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        dsu[i] = Group(i);
    }
    map<pair<int, int>, int> mp;
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        v--;
        g[i] = v;
        mp[{i, v}] = 0;
    }
    vector<tuple<int, int, int, int>> edges;
    for (int i = 1; i <= q; i++) {
        int u, v, k;
        cin >> u >> v >> k;
        u--, v--;
        query[i] = k;
        auto it = mp.find(make_pair(u, g[u]));
        edges.push_back(make_tuple(u, g[u], it->second, i - 1));
        mp.erase(it);
        mp[{u, v}] = i;
        g[u] = v;
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
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
