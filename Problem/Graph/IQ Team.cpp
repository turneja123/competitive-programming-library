//https://www.spoj.com/problems/IQTEAM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 805;

int a[N];
int b[N];
bool mat[N][N];

const long long INF = 1e18;

struct Edge {
    int v, u;
    long long cap, flow = 0;
    Edge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

vector<Edge> edges;
vector<vector<int>> adj;
int idx = 0;
int s, t;
vector<int> level, ptr;
queue<int> q;

void add_edge(int v, int u, long long cap) {
    edges.emplace_back(v, u, cap);
    edges.emplace_back(u, v, 0);
    adj[v].push_back(idx);
    adj[u].push_back(idx + 1);
    idx += 2;
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
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        mat[u][v] = true;
    }
    s = 0, t = n + m + 1;
    adj.resize(t + 1);
    level.resize(t + 1);
    ptr.resize(t + 1);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        add_edge(s, i + 1, a[i]);
        ans += a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        add_edge(i + n + 1, t, b[i]);
        ans += b[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!mat[i][j]) {
                add_edge(i + 1, j + n + 1, INF);
            }
        }
    }
    cout << ans - flow();
    return 0;
}
