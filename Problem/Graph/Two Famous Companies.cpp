//https://www.spoj.com/problems/COMPANYS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int sz[N];
int parent[N];

int dsu_find(int u) {
    if (parent[u] == u) {
        return u;
    }
    return parent[u] = dsu_find(parent[u]);
}

void dsu_unite(int u, int v) {
    if (sz[u] > sz[v]) {
        swap(u, v);
    }
    sz[v] += sz[u];
    parent[u] = v;

}

pair<int, int> calc(int n, int cost, vector<tuple<int, int, int, int>> edges) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    for (auto &[c, x, a, b] : edges) {
        if (x == 0) {
            c += cost;
        }
    }
    sort(edges.begin(), edges.end());
    pair<int, int> ans = {0, 0};
    for (auto [c, x, a, b] : edges) {
        a = dsu_find(a);
        b = dsu_find(b);
        if (a != b) {
            ans.second += c;
            ans.first += x == 0;
            dsu_unite(a, b);
        }
    }
    return ans;
}

int main() {
    IOS;
    int t = 1;
    int n, m, k;
    while (cin >> n >> m >> k) {
        vector<tuple<int, int, int, int>> edges;
        for (int i = 0; i < m; i++) {
            int a, b, c, x;
            cin >> a >> b >> c >> x;
            edges.push_back({c, x, a, b});
        }
        int l = -101, r = 101, opt = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (calc(n, mid, edges).first >= k) {
                l = mid + 1;
                opt = mid;
            } else {
                r = mid - 1;
            }
        }
        int ans = calc(n, opt, edges).second - (ll)k * opt;
        cout << "Case " << t++ << ": " << ans << endl;
    }

    return 0;
}
