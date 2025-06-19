//https://codeforces.com/contest/2117/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

int mn[N];
int parent[N];
int sz[N];
int ans;

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b, int wt, int n) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    int x = dsu_find(0), y = dsu_find(n - 1);
    if ((x == a || x == b) && (y == a || y == b)) {
        ans = min(ans, min({mn[a], mn[b], wt}) + wt);
    }
    mn[a] = min({mn[a], mn[b], wt});
    sz[a] += sz[b];
    parent[b] = a;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            mn[i] = INF;
            parent[i] = i;
            sz[i] = 1;
        }
        vector<tuple<int, int, int>> edges;
        for (int i = 0; i < m; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            edges.push_back(make_tuple(wt, u, v));
        }
        sort(edges.begin(), edges.end());
        ans = 2 * INF;
        for (auto [wt, u, v] : edges) {
            u = dsu_find(u), v = dsu_find(v);
            if (u != v) {
                dsu_unite(u, v, wt, n);
            }
        }
        cout << ans << endl;
    }

    return 0;
}
