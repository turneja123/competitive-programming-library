//https://codeforces.com/contest/1814/problem/F
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
int L[N], R[N];

vector<pair<int, int>> st[N];
vector<pair<int, int>> segtree[4 * N];
vector<tuple<int, int, int, int, int>> restore;

int timer = 0;

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
    for (auto [x, _] : st[b]) {
        if (!ans[x]) {
            st[a].push_back({x, timer});
        }
    }
    int f = (dsu_find(0) == a || dsu_find(0) == b);
    if (f) {
        st[b].clear();
        while (st[a].size()) {
            auto [x, _] = st[a].back();
            ans[x] = 1;
            st[a].pop_back();
        }
    }

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
            restore.push_back(make_tuple(x, sz[x], y, sz[y], timer));
            dsu_unite(x, y);
            ct++;
        }
    }
    timer++;
    if (l == r) {

    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }
    for (int i = 0; i < ct; i++) {
        auto [u, su, v, sv, t] = restore.back();
        parent[u] = u;
        parent[v] = v;
        sz[u] = su;
        sz[v] = sv;
        while (st[u].size() && st[u].back().second >= t) {
            st[u].pop_back();
        }
        while (st[v].size() && st[v].back().second >= t) {
            st[v].pop_back();
        }
        restore.pop_back();
    }
    return;
}

vector<int> adj[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
        st[i].push_back({i, 0});
    }
    timer++;

    for (int i = 0; i < n; i++) {
        cin >> L[i] >> R[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        L[i] = max(L[i], L[0]);
        R[i] = min(R[i], R[0]);
    }

    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            if (u < v) {
                int l = max(L[u], L[v]), r = min(R[u], R[v]);
                if (l <= r) {
                    upd(L[0], R[0], l, r, {u, v}, 0);
                }
            }
        }
    }

    dfs(0, N - 1, 0);
    ans[0] = 1;
    for (int i = 0; i < n; i++) {
        if (ans[i]) {
            cout << i + 1 << " ";
        }
    }


    return 0;
}
