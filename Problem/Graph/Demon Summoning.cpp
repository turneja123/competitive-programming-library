//https://ocpc2026w.eolymp.space/en/compete/9umgdpquih09n7lf096jj2cqvk/problem/4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct DSU {
    vector<int> parent;
    vector<int> sz;

    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        sz.resize(n, 1);
    }

    int dsu_find(int a) {
        if (parent[a] == a) {
            return a;
        }
        return parent[a] = dsu_find(parent[a]);
    }

    void dsu_unite(int a, int b) {
        a = dsu_find(a), b = dsu_find(b);
        if (a == b) {
            return;
        }
        if (sz[b] > sz[a]) {
            swap(a, b);
        }
        sz[a] += sz[b];
        parent[b] = a;
    }
};


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj_x(n), adj_y(n);

        DSU dsu_x(n), dsu_y(n);
        for (int i = 0; i < m; i++) {
            int u, v; string s;
            cin >> u >> s >> v;
            u--, v--;
            if (s == "left") {
                dsu_y.dsu_unite(u, v);
                adj_x[u].push_back(v);
            } else if (s == "right") {
                dsu_y.dsu_unite(u, v);
                adj_x[v].push_back(u);
            } else if (s == "below") {
                dsu_x.dsu_unite(u, v);
                adj_y[u].push_back(v);
            } else {
                dsu_x.dsu_unite(u, v);
                adj_y[v].push_back(u);
            }
        }
        vector<set<int>> adj_leaders_x(n), adj_leaders_y(n);
        vector<int> deg_x(n, 0), deg_y(n, 0);
        vector<int> ans_x(n), ans_y(n);
        vector<int> leaders_x, leaders_y;

        for (int i = 0; i < n; i++) {
            int u = dsu_x.dsu_find(i);
            if (u == i) {
                leaders_x.push_back(i);
            }
            for (int j : adj_x[i]) {
                int v = dsu_x.dsu_find(j);
                int sz = adj_leaders_x[u].size();
                adj_leaders_x[u].insert(v);
                if (sz != adj_leaders_x[u].size()) {
                    deg_x[v]++;
                }
            }
        }
        queue<int> q;
        for (int i : leaders_x) {
            if (deg_x[i] == 0) {
                q.push(i);
            }
        }
        int ctx = 0;
        while (q.size()) {
            int u = q.front();
            q.pop();
            ans_x[u] = ctx++;
            for (int v : adj_leaders_x[u]) {
                deg_x[v]--;
                if (deg_x[v] == 0) {
                    q.push(v);
                }
            }
        }
        if (ctx != leaders_x.size()) {
            cout << "NO" << endl;
            continue;
        }

        for (int i = 0; i < n; i++) {
            int u = dsu_y.dsu_find(i);
            if (u == i) {
                leaders_y.push_back(i);
            }
            for (int j : adj_y[i]) {
                int v = dsu_y.dsu_find(j);
                int sz = adj_leaders_y[u].size();
                adj_leaders_y[u].insert(v);
                if (sz != adj_leaders_y[u].size()) {
                    deg_y[v]++;
                }
            }
        }
        for (int i : leaders_y) {
            if (deg_y[i] == 0) {
                q.push(i);
            }
        }
        int cty = 0;
        while (q.size()) {
            int u = q.front();
            q.pop();
            ans_y[u] = cty++;
            for (int v : adj_leaders_y[u]) {
                deg_y[v]--;
                if (deg_y[v] == 0) {
                    q.push(v);
                }
            }
        }
        if (cty != leaders_y.size()) {
            cout << "NO" << endl;
            continue;
        }

        cout << "YES" << endl;
        for (int i = 0; i < n; i++) {
            int x = dsu_x.dsu_find(i), y = dsu_y.dsu_find(i);
            cout << ans_x[x] + 1 << " " << ans_y[y] + 1 << endl;
        }


    }

    return 0;
}
