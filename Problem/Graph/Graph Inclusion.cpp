//https://codeforces.com/contest/2069/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

int ans[N];

vector<tuple<int, int, int>> segtree[4 * N];
vector<tuple<int, int, int, int, int, int, int, int, int>> restore;
int comps;

struct DSU {
    vector<int> parent;
    vector<int> sz;

    DSU(int n) {
        parent.resize(n);
        sz.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

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
};

DSU da(N), db(N);

void upd(int l, int r, int lq, int rq, tuple<int, int, int> edge, int node) {
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
    for (auto [tp, u, v] : segtree[node]) {
        int xa = da.dsu_find(u), ya = da.dsu_find(v);
        int xb = db.dsu_find(u), yb = db.dsu_find(v);

        restore.push_back(make_tuple(xa, da.sz[xa], ya, da.sz[ya], xb, db.sz[xb], yb, db.sz[yb], comps));
        if (tp == 0) {
            if (xa != ya) {
                da.dsu_unite(xa, ya);
                comps--;
            }
        }
        if (tp == 0 || tp == 1) {
            if (xb != yb) {
                db.dsu_unite(xb, yb);
                comps++;
            }
        }
        ct++;
    }
    if (l == r) {
        ans[l] = comps;
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }
    for (int i = 0; i < ct; i++) {
        auto [xa, sxa, ya, sya, xb, sxb, yb, syb, C] = restore.back();
        da.sz[xa] = sxa;
        da.sz[ya] = sya;
        db.sz[xb] = sxb;
        db.sz[yb] = syb;

        da.parent[xa] = xa;
        da.parent[ya] = ya;
        db.parent[xb] = xb;
        db.parent[yb] = yb;

        comps = C;
        restore.pop_back();
    }
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    comps = 0;
    map<tuple<int, int, int>, int> mp;
    vector<tuple<int, int, int, int, int>> edges;
    for (int i = 0; i < q; i++) {
        char t; int u, v;
        cin >> t >> u >> v;
        u--, v--;
        int tp = (t == 'A' ? 0 : 1);

        if (u > v) {
            swap(u, v);
        }

        auto it = mp.find(make_tuple(tp, u, v));
        if (it != mp.end()) {
            edges.push_back(make_tuple(tp, u, v, it->second, i - 1));
            mp.erase(it);
        } else {
            mp[make_tuple(tp, u, v)] = i;
        }

    }
    while (mp.size()) {
        auto [tp, u, v] = mp.begin()->first;
        edges.push_back(make_tuple(tp, u, v, mp.begin()->second, q - 1));
        mp.erase(mp.begin());
    }
    for (auto [tp, u, v, l, r] : edges) {
        upd(0, q - 1, l, r, make_tuple(tp, u, v), 0);
    }
    dfs(0, q - 1, 0);
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
