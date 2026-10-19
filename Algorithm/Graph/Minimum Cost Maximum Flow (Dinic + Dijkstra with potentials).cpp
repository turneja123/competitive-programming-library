//https://judge.yosupo.jp/problem/assignment
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e18;

struct MCMF {
    struct Edge {
        int from, to;
        ll cap, f, cost;
    };
    int n, s, t, m;

    vector<vector<int>> adj;
    vector<int> ptr;
    vector<ll> dist, pot;
    vector<int> vis;
    vector<Edge> edges;

    MCMF(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t;
        m = 0;
        adj.resize(n);
        ptr.resize(n);
        dist.resize(n);
        pot.resize(n);
        vis.resize(n);
    }

    void add_edge(int u, int v, ll cap, ll cost) {
        adj[u].push_back(m);
        edges.push_back({u, v, cap, 0, cost});
        m++;
        adj[v].push_back(m);
        edges.push_back({v, u, cap, cap, -cost});
        m++;
    }

    int spfa() {
        vector<int> inq(n, 0);
        fill(dist.begin(), dist.end(), INF);
        dist[s] = 0;
        inq[s] = 1;
        queue<int> q;
        q.push(s);
        while (q.size()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for (int e : adj[u]) {
                auto [_, v, cap, f, cost] = edges[e];
                if (cap - f > 0 && dist[v] > dist[u] + cost) {
                    dist[v] = dist[u] + cost;
                    if (!inq[v]) {
                        inq[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return dist[t] != INF;
    }

    int dijkstra() {
        fill(dist.begin(), dist.end(), INF);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        dist[s] = 0;
        pq.push({0, s});
        while (pq.size()) {
            auto [du, u] = pq.top();
            pq.pop();
            if (du != dist[u]) {
                continue;
            }
            for (int e : adj[u]) {
                auto [_, v, cap, f, cost] = edges[e];
                if (cap - f == 0) {
                    continue;
                }
                ll w = cost + pot[u] - pot[v];
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        if (dist[t] == INF) {
            return 0;
        }
        for (int i = 0; i < n; i++) {
            if (dist[i] != INF) {
                pot[i] += dist[i];
            }
        }
        return 1;
    }

    ll dfs(int u, ll pushed) {
        if (!pushed) {
            return 0;
        }
        if (u == t) {
            return pushed;
        }
        vis[u] = 1;
        for (int &i = ptr[u]; i < adj[u].size(); i++) {
            int e = adj[u][i];
            auto [_, v, cap, f, cost] = edges[e];
            if (cap - f == 0 ||
                cost + pot[u] - pot[v] != 0 ||
                vis[v]) {
                continue;
            }
            ll cur = dfs(v, min(pushed, cap - f));
            if (!cur) {
                continue;
            }
            pushed = cur;
            edges[e].f += pushed;
            edges[e ^ 1].f -= pushed;
            vis[u] = 0;
            return pushed;
        }
        vis[u] = 0;
        return 0;
    }

    ll flow(ll k) {
        ll ans = 0, f = 0;
        if (!spfa()) {
            return ans;
        }
        for (int i = 0; i < n; i++) {
            if (dist[i] != INF) {
                pot[i] = dist[i];
            }
        }
        while (f < k) {
            fill(ptr.begin(), ptr.end(), 0);
            while (f < k) {
                ll cur = dfs(s, k - f);
                if (!cur) {
                    break;
                }
                ans += (pot[t] - pot[s]) * cur;
                f += cur;
            }
            if (f == k || !dijkstra()) {
                break;
            }
        }
        return ans;
    }
};

int main() {
    IOS;
    int n;
    cin >> n;
    MCMF mcmf = MCMF(2 * n + 2, 0, 2 * n + 1);
    for (int i = 0; i < n; i++) {
        mcmf.add_edge(0, 1 + i, 1, 0);
    }
    for (int i = 0; i < n; i++) {
        mcmf.add_edge(1 + n + i, 2 * n + 1, 1, 0);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ll a;
            cin >> a;
            mcmf.add_edge(1 + i, 1 + n + j, 1, a);
        }
    }
    cout << mcmf.flow(n) << endl;
    vector<int> ans(n);
    for (int e = 0; e < mcmf.edges.size(); e += 2) {
        auto &edge = mcmf.edges[e];
        if (1 <= edge.from && edge.from <= n && n + 1 <= edge.to && edge.to <= 2 * n && edge.f == 1) {
            ans[edge.from - 1] = edge.to - n - 1;
        }
    }
    for (int v : ans) {
        cout << v << " ";
    }
    return 0;
}
