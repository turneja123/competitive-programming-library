//https://codeforces.com/contest/852/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9;

struct Matching {
    int n, m;

    vector<int> pairU, pairV, dist;
    vector<vector<int>> adj;

    Matching(int _n, int _m) {
        n = _n, m = _m;
        adj.resize(n);
        dist.resize(n);
        pairU.resize(n, -1);
        pairV.resize(m, -1);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < n; u++) {
            if (pairU[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }

        bool f = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] < INF) {
                for (auto v : adj[u]) {
                    if (pairV[v] == -1) {
                        f = true;
                    } else if (dist[pairV[v]] == INF) {
                        dist[pairV[v]] = dist[u] + 1;
                        q.push(pairV[v]);
                    }
                }
            }
        }
        return f;
    }

    bool dfs(int u) {
        if (u != -1) {
            for (auto v : adj[u]) {
                if (pairV[v] == -1 || (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v]))) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    }

    int bpm() {
        for (int i = 0; i < n; i++) {
            pairU[i] = -1;
        }
        for (int i = 0; i < m; i++) {
            pairV[i] = -1;
        }
        while (bfs()) {
            for (int u = 0; u < n; u++) {
                if (pairU[u] == -1) {
                    dfs(u);
                }
            }
        }
        int ans = 0;
        for (int u = 0; u < n; u++) {
            if (pairU[u] != -1) {
                ans++;
            }
        }
        return ans;
    }
};

const int N = 605;

int dist[N][N];

int main() {
    IOS;
    int n, e, m, k;
    cin >> n >> e >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }
    vector<int> p(m);
    for (int i = 0; i < m; i++) {
        cin >> p[i];
        p[i]--;
    }
    for (int i = 0; i < e; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        dist[u][v] = min(dist[u][v], wt);
        dist[v][u] = min(dist[v][u], wt);
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    int l = 0, r = 1731311, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        Matching mc = Matching(m, n);
        for (int i = 0; i < m; i++) {
            int u = p[i];
            for (int v = 0; v < n; v++) {
                if (dist[u][v] <= mid) {
                    mc.add_edge(i, v);
                }
            }
        }
        if (mc.bpm() >= k) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans;
    return 0;
}
