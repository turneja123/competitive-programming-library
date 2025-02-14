//https://dmoj.ca/problem/coci17c5p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

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

void calc(int l, int r, int n, int m, vector<tuple<int, int, int>> a) {
    if (a.empty()) {
        return;
    }
    int mid = (l + r) / 2;
    vector<tuple<int, int, int, int>> restore;
    for (int i = l; i <= mid; i++) {
        int g = m - i;
        for (int j = g; j <= n; j += g) {
            int u = j - 1, v = n + g - 1;
            int x = dsu_find(u), y = dsu_find(v);
            if (x != y) {
                restore.push_back(make_tuple(x, sz[x], y, sz[y]));
                dsu_unite(x, y);
            }
        }
    }

    vector<tuple<int, int, int>> lf, rt;
    for (auto [u, v, j] : a) {
        int x = dsu_find(u), y = dsu_find(v);
        if (x == y) {
            ans[j] = mid;
            lf.push_back(make_tuple(u, v, j));
        } else {
            rt.push_back(make_tuple(u, v, j));
        }
    }
    if (mid + 1 <= r) {
        calc(mid + 1, r, n, m, rt);
    }
    reverse(restore.begin(), restore.end());
    for (auto [u, su, v, sv] : restore) {
        parent[u] = u;
        parent[v] = v;
        sz[u] = su;
        sz[v] = sv;
    }
    if (l <= mid - 1) {
        calc(l, mid - 1, n, m, lf);
    }
}

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n + m; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        queries.push_back(make_tuple(u, v, i));
    }
    calc(0, m - 1, n, m, queries);
    for (int i = 0; i < q; i++) {
        cout << ans[i] + 1 << endl;
    }
    return 0;
}
