//https://www.spoj.com/problems/SPECIALG/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 19;

int up[K][N];
int tim[K][N];
int color[N];
int group[N];
bool cycle[N];
int pos[N];
int entry[N];
int sz[N];
int dist[N];
int parent[N];

void dfs(int u, int p) {
    color[u] = 1;
    parent[u] = p;
    int v = up[0][u];
    if (color[v] == 0) {
        dfs(v, u);
    } else if (color[v] == 1) {
        int x = u;
        vector<int> cyc;
        while (x != v) {
            cyc.push_back(x);
            x = parent[x];
        }
        cyc.push_back(v);
        reverse(cyc.begin(), cyc.end());
        for (int i = 0; i < cyc.size(); i++) {
            int x = cyc[i];
            cycle[x] = true;
            pos[x] = i;
            dist[x] = 0;
            sz[x] = cyc.size();
            group[x] = v;
        }
    }
    color[u] = 2;
    if (!cycle[u]) {
        group[u] = group[v];
        if (cycle[v]) {
            dist[u] = 1;
            entry[u] = v;
        } else {
            dist[u] = dist[v] + 1;
            entry[u] = entry[v];
        }
    }
}

pair<int, int> kth(int u, int k) {
    int mn = N;
    for (int i = K - 1; i >= 0; i--) {
        int c = k & (1 << i);
        if (c) {
            mn = min(mn, tim[i][u]);
            u = up[i][u];
        }
    }
    return {u, mn};
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int j;
        cin >> j;
        up[0][i] = j;
        tim[0][i] = N;
    }
    up[0][0] = 0;
    tim[0][0] = N;
    vector<tuple<int, int, int>> queries;
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int u;
            cin >> u;
            tim[0][u] = i;
        } else {
            int u, v;
            cin >> u >> v;
            queries.push_back({i, u, v});
        }
    }
    for (int k = 1; k < K; k++) {
        for (int i = 0; i <= n; i++) {
            up[k][i] = up[k - 1][up[k - 1][i]];
            tim[k][i] = min(tim[k - 1][i], tim[k - 1][up[k - 1][i]]);
        }
    }
    for (int i = 0, j = 0; i <= n; i++) {
        if (color[i] == 0) {
            dfs(i, i);
        }
    }
    for (auto [t, u, v] : queries) {
        if (group[u] != group[v] || (cycle[u] && !cycle[v]) || dist[v] > dist[u]) {
            cout << -1 << endl;
            continue;
        }
        if (!cycle[u] && !cycle[v]) {
            pair<int, int> k = kth(u, dist[u] - dist[v]);
            if (k.first != v || k.second < t) {
                cout << -1 << endl;
            } else {
                cout << dist[u] - dist[v] << endl;
            }
        }
        if (!cycle[u] && cycle[v]) {
            pair<int, int> k = kth(u, dist[u]);
            if (k.second < t) {
                cout << -1 << endl;
                continue;
            }
            int d = dist[u];
            int l = pos[k.first], r = pos[v];
            if (l <= r) {
                k = kth(k.first, r - l);
                d += r - l;
            } else {
                k = kth(k.first, r + sz[v] - l);
                d += r + sz[v] - l;
            }
            if (k.second < t) {
                cout << -1 << endl;
            } else {
                cout << d << endl;
            }
        }
        if (cycle[u] && cycle[v]) {
            int d = 0;
            int l = pos[u], r = pos[v];
            pair<int, int> k;
            if (l <= r) {
                k = kth(u, r - l);
                d += r - l;
            } else {
                k = kth(u, r + sz[v] - l);
                d += r + sz[v] - l;
            }
            if (k.second < t) {
                cout << -1 << endl;
            } else {
                cout << d << endl;
            }
        }
    }
    return 0;
}
