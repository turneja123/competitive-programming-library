//https://cses.fi/problemset/task/1695/
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
    int v, u;
    long long cap, flow = 0;
    Edge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

vector<Edge> edges;
vector<vector<int>> adj;
int n, e, m = 0;
int s, t;
vector<int> level, ptr;
queue<int> q;
bool vis[N];

void add_edge(int v, int u, long long cap) {
    edges.emplace_back(v, u, cap);
    edges.emplace_back(u, v, 0);
    adj[v].push_back(m);
    adj[u].push_back(m + 1);
    m += 2;
}

bool bfs() {
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int id : adj[v]) {
            if (edges[id].cap - edges[id].flow < 1) {
                continue;
            }
            if (level[edges[id].u] != -1) {
                continue;
            }
            level[edges[id].u] = level[v] + 1;
            q.push(edges[id].u);
        }
    }
    return level[t] != -1;
}

long long dfs(int v, long long pushed) {
    if (pushed == 0) {
        return 0;
    }
    if (v == t) {
        return pushed;
    }
    for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
        int id = adj[v][cid];
        int u = edges[id].u;
        if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) {
            continue;
        }
        long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
        if (tr == 0) {
            continue;
        }
        edges[id].flow += tr;
        edges[id ^ 1].flow -= tr;
        return tr;
    }
    return 0;
}

long long flow() {
    long long f = 0;
    while (true) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        q.push(s);
        if (!bfs()) {
            break;
        }
        fill(ptr.begin(), ptr.end(), 0);
        while (long long pushed = dfs(s, INF)) {
            f += pushed;
        }
    }
    return f;
}
int main() {
    IOS;
    cin >> n >> e;
    adj.resize(n + 1);
    level.resize(n + 1);
    ptr.resize(n + 1);
    s = 0, t = n - 1;
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        add_edge(u, v, 1);
        add_edge(v, u, 1);
    }
    cout << flow() << endl;
    queue<int> q;
    q.push(0);
    vis[0] = true;
    while (q.size()) {
        int v = q.front();
        q.pop();
        for (int e : adj[v]) {
            if (edges[e].cap - edges[e].flow > 0 && !vis[edges[e].u]) {
                vis[edges[e].u] = true;
                q.push(edges[e].u);
            }
        }
    }
    for (int i = 0; i < edges.size(); i += 2) {
        if (vis[edges[i].v] && !vis[edges[i].u]) {
            cout << edges[i].v + 1 << " " << edges[i].u + 1 << endl;
        }
    }
    return 0;
}
