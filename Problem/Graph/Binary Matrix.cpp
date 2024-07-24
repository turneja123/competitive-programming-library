//https://www.spoj.com/problems/BNMT/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2505;
const int INF = 1e9;

string a[N];

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

int min_cost_flow(int N) {
    int flow = 0;
    int ans = 0;
    vector<int> d;
    vector<bool> vis;
    while (1) {
        shortest_paths(N, d, vis);
        if (d[t] == INF) {
            break;
        }
        vector<int> ptr(N, 0);
        int f = dfs(s, INF, ptr, vis, d);
        flow += f;
        ans += d[t] * f;
    }
    return ans;
}


int main() {
    IOS;
    int c;
    cin >> c;
    for (int tt = 1; tt <= c; tt++) {
        int n, m, ct = 0;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ct += ((a[i][j] == '1') ? 1 : 0);
            }
        }
        s = 0, t = 1 + n + m;
        int ans = INF;
        for (int one_r = 0; one_r <= m; one_r++) {
            int one_c = (n * one_r) / m;
            if (one_c * m != one_r * n) {
                continue;
            }
            if (ct - one_r * n > ans) {
                continue;
            }
            for (int i = 0; i < n; i++) {
                add_edge(s, 1 + i, one_r, 0);
            }
            for (int j = 0; j < m; j++) {
                add_edge(1 + n + j, t, one_c, 0);
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    int cost = ((a[i][j] == '1') ? 0 : 1);
                    add_edge(1 + i, 1 + n + j, 1, cost);
                }
            }
            int cost = min_cost_flow(t + 1), cur = ct - one_r * n + 2 * cost;
            if (cur > ans) {
                break;
            }
            ans = min(ans, cur);
            for (int i = 0; i <= t; i++) {
                adj[i].clear();
            }
            edges.clear();
        }

        if (ans == INF) {
            ans = -1;
        }
        cout << "Case " << tt << ": " << ans << endl;

    }
    return 0;
}
