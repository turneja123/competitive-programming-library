//https://cses.fi/problemset/task/2130/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2505;
const int INF = 1e9;

int s, t;

struct Edge {
    int u, v;
    int cap, cost;
    Edge(int u, int v, int cap, int cost) : u(u), v(v), cap(cap), cost(cost) {}
};

vector<int> adj[N];
vector<Edge> edges;

void add_edge(int u, int v, int cap, int cost) {
    if (cap == 0) {
        return;
    }
    adj[u].push_back(edges.size());
    edges.emplace_back(u, v, cap, cost);
    adj[v].push_back(edges.size());
    edges.emplace_back(v, u, 0, -cost);
}

void shortest_paths(int n, vector<int>& d, vector<bool> &inq) {
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

int dfs(int u, int pushed, vector<int> &ptr, vector<bool> &vis, vector<int> &d) {
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

int min_cost_flow(int N, int k) {
    int flow = 0;
    int ans = 0;
    vector<int> d;
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
    int n, e, f;
    cin >> n >> e >> f;
    s = 0, t = n - 1;
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        add_edge(u, v, 1, 1);
    }
    int c = min_cost_flow(n, f);
    cout << c << endl;
    if (c == -1) {
        return 0;
    }
    for (int i = 0; i < f; i++) {
        int u = 0;
        vector<int> path{u};
        while (u != n - 1) {
            for (int e : adj[u]) {
                if (edges[e].cost > 0 && edges[e].cap == 0) {
                    edges[e].cap = 1;
                    u = edges[e].v;
                    path.push_back(u);
                    break;
                }
            }
        }
        cout << path.size() << endl;
        for (int v : path) {
            cout << v + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}
