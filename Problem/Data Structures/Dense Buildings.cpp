//https://atcoder.jp/contests/abc394/tasks/abc394_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const int M = 5e5 + 5;
const int INF = 1e9;

vector<tuple<int, int, int>> edges;

int n, m;

int parent[M];
int sz[M];
int a[N][N];
int ans[M];

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

void calc(int l, int r, vector<tuple<int, int, int, int, int, int, int>> a) {
    if (a.empty()) {
        return;
    }
    int mid = (l + r) / 2;
    int e = get<0>(edges[mid]);
    vector<tuple<int, int, int, int>> restore;
    for (int i = mid; i <= r; i++) {
        int u = get<1>(edges[i]), v = get<2>(edges[i]);
        int x = dsu_find(u), y = dsu_find(v);
        if (x != y) {
            restore.push_back(make_tuple(x, sz[x], y, sz[y]));
            dsu_unite(x, y);
        }
    }
    vector<tuple<int, int, int, int, int, int, int>> lf, rt;
    for (auto [a, b, y, c, d, z, i] : a) {
        int u = a * m + b, v = c * m + d;
        if (dsu_find(u) == dsu_find(v)) {
            int cur = 0;
            int mn = min(y, e);
            if (mn < y) {
                cur += y - mn;
            }
            cur += abs(mn - z);
            ans[i] = min(ans[i],cur);
            rt.push_back(make_tuple(a, b, y, c, d, z, i));
        } else {
            lf.push_back(make_tuple(a, b, y, c, d, z, i));
        }
    }
    if (l <= mid - 1) {
        calc(l, mid - 1, lf);
    }
    reverse(restore.begin(), restore.end());
    for (auto [u, su, v, sv] : restore) {
        parent[u] = u;
        parent[v] = v;
        sz[u] = su;
        sz[v] = sv;
    }
    if (mid + 1 <= r) {
        calc(mid + 1, r, rt);
    }
    return;
}

int main() {
    IOS;
    cin >> n >> m;
    for (int i = 0; i < n * m; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i != n - 1) {
                edges.push_back(make_tuple(min(a[i][j], a[i + 1][j]), i * m + j, (i + 1) * m + j));
            }
            if (j != m - 1) {
                edges.push_back(make_tuple(min(a[i][j], a[i][j + 1]), i * m + j, i * m + j + 1));
            }
        }
    }
    sort(edges.begin(), edges.end());
    int q;
    cin >> q;
    vector<tuple<int, int, int, int, int, int, int>> queries;
    for (int i = 0; i < q; i++) {
        int a, b, y, c, d, z;
        cin >> a >> b >> y >> c >> d >> z;
        a--, b--, c--, d--;
        queries.push_back(make_tuple(a, b, y, c, d, z, i));
        if (a == c && b == d) {
            ans[i] = abs(y-z);
        } else {
            ans[i] = INF;
        }
    }
    if (edges.size()) {
        calc(0, edges.size() - 1, queries);
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
