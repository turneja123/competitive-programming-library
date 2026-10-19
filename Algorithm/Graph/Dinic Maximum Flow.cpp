//https://www.spoj.com/problems/FASTFLOW/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e18;

struct Flow {
    struct Edge {
        int from, to;
        ll cap, f;
    };

    int n, m, s, t;
    vector<vector<int>> adj;
    vector<int> ptr;
    vector<int> level;
    vector<Edge> edges;

    Flow(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t;
        m = 0;
        adj.resize(n);
        ptr.resize(n);
        level.resize(n);
    }

    void add_edge(int u, int v, ll cap) {
        edges.push_back({u, v, cap, 0});
        adj[u].push_back(m);
        m++;
        edges.push_back({v, u, cap, cap});
        adj[v].push_back(m);
        m++;
    }

    int bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int e : adj[u]) {
                int v = edges[e].to;
                if (edges[e].cap - edges[e].f > 0 && level[v] == -1) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] != -1;
    }

    ll dfs(int u, ll pushed) {
        if (!pushed) {
            return 0;
        }
        if (u == t) {
            return pushed;
        }
        for (int &i = ptr[u]; i < adj[u].size(); i++) {
            int e = adj[u][i];
            int v = edges[e].to;
            if (edges[e].cap - edges[e].f == 0 || level[v] != level[u] + 1) {
                continue;
            }
            ll cur = dfs(v, min(pushed, edges[e].cap - edges[e].f));
            if (cur == 0) {
                continue;
            }
            pushed = cur;
            edges[e].f += pushed;
            edges[e ^ 1].f -= pushed;
            return pushed;
        }
        return 0;
    }

    ll flow() {
        ll f = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (1) {
                ll cur = dfs(s, INF);
                if (cur == 0) {
                    break;
                }
                f += cur;
            }
        }
        return f;
    }
};


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    Flow flow(n, 0, n - 1);
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        u--, v--;
        flow.add_edge(u, v, w);
        flow.add_edge(v, u, w);
    }
    cout << flow.flow();
    return 0;
}
