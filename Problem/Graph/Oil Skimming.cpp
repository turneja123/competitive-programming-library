//https://www.eolymp.com/en/problems/3052
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 605;
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
int a[N][N];

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
    int q;
    cin >> q;
    for (int p = 1; p <= q; p++) {
        cin >> n;
        s = 0, t = 1 + n * n;
        adj.resize(2 + n * n);
        level.resize(2 + n * n);
        ptr.resize(2 + n * n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                char c;
                cin >> c;
                if (c == '#') {
                    a[i][j] = 1;
                } else {
                    a[i][j] = 0;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!a[i][j]) {
                    continue;
                }
                int idx = 1 + j + i * n;
                if ((i + j) % 2 == 0) {
                    add_edge(0, idx, 1);
                    if (i > 0 && a[i - 1][j]) {
                        add_edge(idx, idx - n, 1);
                    }
                    if (i < n - 1 && a[i + 1][j]) {
                        add_edge(idx, idx + n, 1);
                    }
                    if (j > 0 && a[i][j - 1]) {
                        add_edge(idx, idx - 1, 1);
                    }
                    if (j < n - 1 && a[i][j + 1]) {
                        add_edge(idx, idx + 1, 1);
                    }
                } else {
                    add_edge(idx, t, 1);
                }
            }
        }
        cout << "Case " << p << ": " << flow() << endl;
        edges.clear();
        adj.clear();
        level.clear();
        ptr.clear();
        m = 0;
    }
    return 0;
}
