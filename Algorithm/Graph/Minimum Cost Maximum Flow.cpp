//https://cses.fi/problemset/task/2121/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const int INF = 1e9;

struct Edge {
    int u, v;
    int cap, cost;
    Edge(int u, int v, int cap, int cost) : u(u), v(v), cap(cap), cost(cost) {}
};

vector<int> adj[N];
vector<Edge> edges;

void add_edge(int u, int v, int cap, int cost) {
    adj[u].push_back(edges.size());
    edges.emplace_back(u, v, cap, cost);
    adj[v].push_back(edges.size());
    edges.emplace_back(v, u, 0, -cost);
}

void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    priority_queue<pair<int, int>> q;
    q.push(make_pair(0, v0));
    p.assign(n, -1);
    while (!q.empty()) {
        int u = q.top().second, nw = -q.top().first;
        q.pop();
        if (nw != d[u]) {
            continue;
        }
        for (int e : adj[u]) {
            int v = edges[e].v;
            if (edges[e].cap > 0 && d[v] > d[u] + edges[e].cost) {
                d[v] = d[u] + edges[e].cost;
                p[v] = e;
                q.push(make_pair(-d[v], v));

            }
        }
    }
}

int min_cost_flow(int N, int K, int s, int t) {
    int flow = 0;
    int ans = 0;
    vector<int> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF) {
            break;
        }

        int f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, edges[p[cur]].cap);
            cur = edges[p[cur]].u;
        }
        flow += f;
        ans += f * d[t];
        cur = t;
        while (cur != s) {
            edges[p[cur]].cap -= f;
            edges[p[cur] ^ 1].cap += f;
            cur = edges[p[cur]].u;
        }
    }

    if (flow < K) {
        return -1;
    } else {
        return ans;
    }
}


int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        u--, v--;
        if (u == v) {
            continue;
        }
        add_edge(u, v, x, y);
    }
    cout << min_cost_flow(n, k, 0, n - 1);
    return 0;
}
