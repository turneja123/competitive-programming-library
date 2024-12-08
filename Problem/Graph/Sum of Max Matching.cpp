//https://atcoder.jp/contests/abc383/tasks/abc383_e
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
int cta[N];
int ctb[N];

vector<int> adj[N];
tuple<int, int, int> edge[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b, bool f = false) {
    a = dsu_find(a);
    b = dsu_find(b);
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    if (f) {
        cta[a] += cta[b];
        ctb[a] += ctb[b];
    }
    sz[a] += sz[b];
    parent[b] = a;
}

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int a, b, wt;
        cin >> a >> b >> wt;
        a--, b--;
        edge[i] = make_tuple(wt, a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        x--;
        cta[x]++;
    }
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        x--;
        ctb[x]++;
    }

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    sort(edge, edge + m);
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int wt = get<0>(edge[i]);
        int a = get<1>(edge[i]);
        int b = get<2>(edge[i]);
        int p1 = dsu_find(a);
        int p2 = dsu_find(b);
        if (p1 != p2) {
            dsu_unite(p1, p2);
            edges.push_back(make_tuple(a, b, wt));
        }
    }
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    long long ans = 0;
    for (int i = 0; i < n - 1; i++) {
        auto [u, v, wt] = edges[i];
        int p1 = dsu_find(u);
        int p2 = dsu_find(v);
        if (p1 != p2) {
            dsu_unite(p1, p2, true);
            int x = dsu_find(p1);
            int mn = min(cta[x], ctb[x]);
            ans += (long long) wt * mn;
            cta[x] -= mn, ctb[x] -= mn;
        }
    }
    cout << ans;
    return 0;
}
