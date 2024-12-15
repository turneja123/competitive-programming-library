//https://www.spoj.com/problems/SELLPHN2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const int INF = 1e9;

struct Edge {
    int v, u;
    int cap, flow = 0;
    Edge(int v, int u, int cap) : v(v), u(u), cap(cap) {}
};

vector<Edge> edges;
vector<vector<int>> adj;
int idx = 0;
int s, t;
vector<int> level, ptr;
queue<int> q;

void add_edge(int v, int u, int cap) {
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

int dfs(int v, int pushed) {
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
        int tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
        if (tr == 0) {
            continue;
        }
        edges[id].flow += tr;
        edges[id ^ 1].flow -= tr;
        return tr;
    }
    return 0;
}

int flow() {
    int f = 0;
    while (true) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        q.push(s);
        if (!bfs()) {
            break;
        }
        fill(ptr.begin(), ptr.end(), 0);
        while (int pushed = dfs(s, INF)) {
            f += pushed;
        }
    }
    return f;
}
int main() {
    IOS;
    int tt;
    cin >> tt;
    while (tt--) {
        int l, m, n;
        cin >> l >> m >> n;
        s = 0, t = 2 + n + m;
        adj.resize(t + 1);
        level.resize(t + 1);
        ptr.resize(t + 1);
        add_edge(s, 1, l);
        for (int i = 0; i < m; i++) {
            int f;
            cin >> f;
            add_edge(1, i + 2, f);
        }
        for (int i = 0; i < n; i++) {
            int f;
            cin >> f;
            add_edge(m + i + 2, t, f);
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int f;
                cin >> f;
                add_edge(i + 2, m + j + 2, f);
            }
        }
        cout << flow() << endl;
        adj.clear();
        level.clear();
        ptr.clear();
        edges.clear();
        idx = 0;
    }
    return 0;
}
