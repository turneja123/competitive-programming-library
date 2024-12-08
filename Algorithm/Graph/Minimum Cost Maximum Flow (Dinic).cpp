//https://judge.yosupo.jp/problem/assignment
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2505;
const long long INF = 1e18;

int s, t;

struct Edge {
    int u, v;
    int cap; long long cost;
    Edge(int u, int v, int cap, long long cost) : u(u), v(v), cap(cap), cost(cost) {}
};

vector<int> adj[N];
vector<Edge> edges;

void add_edge(int u, int v, int cap, long long cost) {
    if (cap == 0) {
        return;
    }
    adj[u].push_back(edges.size());
    edges.emplace_back(u, v, cap, cost);
    adj[v].push_back(edges.size());
    edges.emplace_back(v, u, 0, -cost);
}

void shortest_paths(int n, vector<long long>& d, vector<bool> &inq) {
    d.assign(n, INF);
    inq.assign(n, false);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int e : adj[u]) {
            int v = edges[e].v;
            if (edges[e].cap > 0 && d[v] > d[u] + edges[e].cost) {
                d[v] = d[u] + edges[e].cost;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int dfs(int u, int pushed, vector<int> &ptr, vector<bool> &vis, vector<long long> &d) {
    if (u == t) {
        return pushed;
    }
    int ans = 0;
    vis[u] = true;
    for (int& cid = ptr[u]; cid < (int)adj[u].size(); cid++) {
        int id = adj[u][cid];
        int v = edges[id].v;
        if (edges[id].cap > 0 && d[v] == d[u] + edges[id].cost && !vis[v]) {
            int tr = dfs(v, min(pushed, edges[id].cap), ptr, vis, d);
            ans += tr;
            edges[id].cap -= tr;
            edges[id ^ 1].cap += tr;
            pushed -= tr;
            if (pushed == 0) {
                vis[u] = false;
                break;
            }
        }
    }
    return ans;
}

long long min_cost_flow(int N, int k) {
    int flow = 0;
    long long ans = 0;
    vector<long long> d;
    vector<bool> vis;
    while (flow < k) {
        shortest_paths(N, d, vis);
        if (d[t] == INF) {
            break;
        }
        vector<int> ptr(N, 0);
        int f = dfs(s, k - flow, ptr, vis, d);
        flow += f;
        ans += d[t] * f;
    }
    if (flow < k) {
        return -1;
    }
    return ans;
}

int main() {
    IOS;
    int n;
    cin >> n;
    s = 0, t = 2 * n + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c;
            cin >> c;
            add_edge(i + 1, j + n + 1, 1, c);
        }
    }
    for (int i = 0; i < n; i++) {
        add_edge(s, i + 1, 1, 0);
        add_edge(i + n + 1, t, 1, 0);
    }
    long long c = min_cost_flow(t + 1, n);
    cout << c << endl;
    vector<int> ans(n);
    for (int e = 0; e < edges.size(); e += 2) {
        if (edges[e].cap == 0 && edges[e].cost != 0) {
            ans[edges[e].u - 1] = edges[e].v - n - 1;
        }
    }
    for (int v : ans) {
        cout << v << " ";
    }

    return 0;
}
