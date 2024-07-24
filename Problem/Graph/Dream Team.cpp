//https://atcoder.jp/contests/abc247/tasks/abc247_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 150;

const long long K = 1e12;
const long long INF = 1e18;

struct Edge {
    int u, v;
    int cap; long long cost;
    Edge(int u, int v, int cap, long long cost) : u(u), v(v), cap(cap), cost(cost) {}
};

vector<int> adj[2 * N + 5];
vector<Edge> edges;

int s, t;

void add_edge(int u, int v, int cap, long long cost) {
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
            long long wt = edges[e].cost;
            if (edges[e].cap > 0 && d[v] > d[u] + wt) {
                d[v] = d[u] + wt;
                p[v] = e;
                q.push(make_pair(-d[v], v));
            }
        }
    }
}

long long min_cost_flow(int n, int k) {
    int flow = 0;
    long long ans = 0;
    vector<int> p; vector<long long> d;

    while (flow < k) {
        shortest_paths(n, s, d, p);
        if (d[t] == INF) {
            break;
        }

        int f = k - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, edges[p[cur]].cap);
            cur = edges[p[cur]].u;
        }
        flow += f;
        ans += (long long)f * d[t];
        cur = t;
        while (cur != s) {
            edges[p[cur]].cap -= f;
            edges[p[cur] ^ 1].cap += f;
            cur = edges[p[cur]].u;
        }
    }

    if (flow < k) {
        return -1;
    } else {
        return ans;
    }
}


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int u, v; long long x;
        cin >> u >> v >> x;
        u--, v--;
        add_edge(u + 1, v + 1 + N, 1, K - x);
    }
    s = 0, t = 2 * N + 1;
    for (int i = 0; i < N; i++) {
        add_edge(s, i + 1, 1, 0);
        add_edge(i + 1 + N, t, 1, 0);
    }
    vector<long long> costs;
    long long ans = 0;
    for (int i = 1; i <= N; i++) {
        long long cur = min_cost_flow(2 * N + 2, 1);
        if (cur == -1) {
            break;
        }
        ans += cur;
        costs.push_back(K * i - ans);
    }
    cout << costs.size() << endl;
    for (long long x : costs) {
        cout << x << endl;
    }
    return 0;
}
