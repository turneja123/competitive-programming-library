//https://atcoder.jp/contests/abc407/tasks/abc407_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const long long INF = 1e18;

struct Edge {
    int u, v;
    int cap; long long cost;
    Edge(int u, int v, long long cap, long long cost) : u(u), v(v), cap(cap), cost(cost) {}
};

vector<int> adj[N];
vector<Edge> edges;

void add_edge(int u, int v, long long cap, long long  cost) {
    adj[u].push_back(edges.size());
    edges.emplace_back(u, v, cap, cost);
    adj[v].push_back(edges.size());
    edges.emplace_back(v, u, 0, -cost);
}

void shortest_paths(int n, int v0, vector<long long>& d, vector<int>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    priority_queue<pair<long long, int>> q;
    q.push(make_pair(0, v0));
    p.assign(n, -1);
    while (!q.empty()) {
        int u = q.top().second; long long nw = -q.top().first;
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

long long min_cost_flow(int N, int s, int t) {
    int flow = 0;
    long long ans = 0;
    vector<long long> d; vector<int> p;
    while (1) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF) {
            break;
        }
        int f = 1;
        int cur = t;
        while (cur != s) {
            f = min(f, edges[p[cur]].cap);
            cur = edges[p[cur]].u;
        }
        if (f == 0) {
            return ans;
        }
        flow += f;
        if (d[t] >= 0) {
            return ans;
        }
        ans += d[t];
        cur = t;
        while (cur != s) {
            edges[p[cur]].cap -= f;
            edges[p[cur] ^ 1].cap += f;
            cur = edges[p[cur]].u;
        }
    }
    return ans;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> a(n, vector<long long>(m, 0));
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            ans += a[i][j];
        }
    }
    int s = 0, t = 1 + n * m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!a[i][j]) {
                continue;
            }
            int idx = 1 + j + i * m;
            if ((i + j) % 2 == 0) {
                add_edge(0, idx, 1, a[i][j]);
                if (i > 0 && a[i - 1][j]) {
                    add_edge(idx, idx - m, 1, 0);
                }
                if (i < n - 1 && a[i + 1][j]) {
                    add_edge(idx, idx + m, 1, 0);
                }
                if (j > 0 && a[i][j - 1]) {
                    add_edge(idx, idx - 1, 1, 0);
                }
                if (j < m - 1 && a[i][j + 1]) {
                    add_edge(idx, idx + 1, 1, 0);
                }
            } else {
                add_edge(idx, t, 1, a[i][j]);
            }
        }
    }
    cout << ans - min_cost_flow(t + 1, s, t);
    return 0;
}
