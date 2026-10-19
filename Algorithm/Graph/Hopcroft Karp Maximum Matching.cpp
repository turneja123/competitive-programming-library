//https://judge.yosupo.jp/problem/bipartitematching
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct Matching {
    int n, m;
    vector<vector<int>> adj;
    vector<int> dist, pairU, pairV;

    Matching(int _n, int _m) {
        n = _n;
        m = _m;
        adj.resize(n);
        dist.resize(n);
        pairU.resize(n, -1);
        pairV.resize(m, -1);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    int bfs() {
        fill(dist.begin(), dist.end(), -1);
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (pairU[i] == -1) {
                q.push(i);
                dist[i] = 0;
            }
        }
        int ok = 0;
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (pairV[v] == -1) {
                    ok = 1;
                } else {
                    int x = pairV[v];
                    if (dist[x] == -1) {
                        dist[x] = dist[u] + 1;
                        q.push(x);
                    }
                }
            }
        }
        return ok;
    }
    int dfs(int u) {
        for (int v : adj[u]) {
            if (pairV[v] == -1) {
                pairU[u] = v;
                pairV[v] = u;
                return 1;
            }
            int x = pairV[v];
            if (dist[x] == dist[u] + 1 && dfs(x)) {
                pairU[u] = v;
                pairV[v] = u;
                return 1;
            }
        }
        dist[u] = -1;
        return 0;
    }

    int matching() {
        int ans = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++) {
                if (pairU[i] == -1 && dfs(i)) {
                    ans++;
                }
            }
        }
        return ans;
    }
};


int main() {
    IOS;
    int n, m, e;
    cin >> n >> m >> e;
    Matching mc = Matching(n, m);
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        mc.add_edge(u, v);
    }
    cout << mc.matching() << endl;
    for (int i = 0; i < n; i++) {
        if (mc.pairU[i] != -1) {
            cout << i << " " << mc.pairU[i] << endl;
        }
    }

    return 0;
}
