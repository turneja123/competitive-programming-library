//https://ocpc2025s.eolymp.space/en/compete/sk55ojcma10djasruv04qdm2fo/problem/5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 40005;
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

int a[105][105];
int b[105][105];
int dir[105][105];

int main() {
    IOS;
    int te;
    cin >> te;
    while (te--) {
        int r, c;
        cin >> r >> c;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cin >> a[i][j];
            }
        }
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cin >> b[i][j];
            }
        }
        int can = 1;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                dir[i][j] = 0;
                if (i != 0) {
                    dir[i][j]++;
                }
                if (i != r - 1) {
                    dir[i][j]++;
                }
                if (j != 0) {
                    dir[i][j]++;
                }
                if (j != c - 1) {
                    dir[i][j]++;
                }
                if (a[i][j] + b[i][j] != dir[i][j]) {
                    can = 0;
                }
            }
        }
        if (can == 0) {
            cout << "Nostad" << endl;
            continue;
        }

        n = r * c + 1;
        adj.resize(n + 1);
        level.resize(n + 1);
        ptr.resize(n + 1);
        s = 0, t = n;
        int x = 0, y = 0;
        for (int i = 0; i < r; i++) {
            int d = (i + 1) % 2;
            for (int j = 0; j < c; j++, d++) {
                int id = 1 + i * c + j;
                if (d % 2 == 1) {
                    add_edge(s, id, a[i][j]);
                    if (i != r - 1) {
                        add_edge(id, id + c, 1);
                    }
                    if (j != c - 1) {
                        add_edge(id, id + 1, 1);
                    }
                    if (i != 0) {
                        add_edge(id, id - c, 1);
                    }
                    if (j != 0) {
                        add_edge(id, id - 1, 1);
                    }
                    x += a[i][j];
                } else {
                    y += b[i][j];
                    add_edge(id, t, b[i][j]);
                }

            }
        }
        int f = flow();
        if (f == x && f == y) {
            cout << "Ostad" << endl;
        } else {
            cout << "Nostad" << endl;
        }
        adj.clear();
        level.clear();
        ptr.clear();
        edges.clear();
        m = 0;
    }
    return 0;
}
