//https://atcoder.jp/contests/agc002/tasks/agc002_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

vector<pair<int, int>> edges;
bool seen[N];
int parent[N];
int sz[N];
int ans[N];

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

void calc(int l, int r, vector<tuple<int, int, int, int>> a) {
    if (a.empty()) {
        return;
    }
    int mid = (l + r) / 2;
    vector<tuple<int, int, int, int>> restore;
    for (int i = l; i <= mid; i++) {
        auto [u, v] = edges[i];
        int x = dsu_find(u), y = dsu_find(v);
        if (x != y) {
            restore.push_back(make_tuple(x, sz[x], y, sz[y]));
            dsu_unite(x, y);
        }
    }
    vector<tuple<int, int, int, int>> lf, rt;
    for (auto [u, v, z, j] : a) {
        int x = dsu_find(u), y = dsu_find(v);
        int ct = sz[x];
        if (y != x) {
            ct += sz[y];
        }
        if (ct >= z) {
            ans[j] = mid;
            lf.push_back(make_tuple(u, v, z, j));
        } else {
            rt.push_back(make_tuple(u, v, z, j));
        }
    }
    if (mid + 1 <= r) {
        calc(mid + 1, r, rt);
    }
    reverse(restore.begin(), restore.end());
    for (auto [u, su, v, sv] : restore) {
        parent[u] = u;
        parent[v] = v;
        sz[u] = su;
        sz[v] = sv;
    }
    if (l <= mid - 1) {
        calc(l, mid - 1, lf);
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        edges.push_back(make_pair(u, v));
    }
    int q;
    cin >> q;
    vector<tuple<int, int, int, int>> queries;
    for (int i = 0; i < q; i++) {
        int u, v, z;
        cin >> u >> v >> z;
        u--, v--;
        queries.push_back(make_tuple(u, v, z, i));
    }
    calc(0, m - 1, queries);
    for (int i = 0; i < q; i++) {
        cout << ans[i] + 1 << endl;
    }
    return 0;
}
