//https://dmoj.ca/problem/bbc09b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const int INF = 1e9;
const int K = 5e5;

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
    int n, m;
    cin >> n;
    string a;
    cin >> a;
    int s = 0, t = n + 1;
    add_edge(s, 1, INF, 0);
    cin >> m;
    for (int i = 0; i < n; i++) {
        add_edge(i + 1, i + 2, INF, 0);
    }
    for (int i = 0; i < m; i++) {
        string x; int p;
        cin >> x >> p;
        for (int j = 0; j <= n - (int)x.size(); j++) {
            string tmp = a.substr(j, (int)x.size());
            if (tmp == x) {
                add_edge(j + 1, j + 1 + x.size(), 1, -p);
            }
        }
    }
    int x;
    cin >> x;
    cout << -min_cost_flow(n + 2, x, s, t);

    return 0;
}
