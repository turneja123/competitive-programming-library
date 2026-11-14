//https://qoj.ac/contest/2509/problem/14097
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e18;

struct Flow {
    struct Edge {
        int from, to;
        ll cap, f;
    };

    int n, m, s, t;
    vector<vector<int>> adj;
    vector<int> ptr;
    vector<int> level;
    vector<Edge> edges;

    Flow(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t;
        m = 0;
        adj.resize(n);
        ptr.resize(n);
        level.resize(n);
    }

    void add_edge(int u, int v, ll cap) {
        edges.push_back({u, v, cap, 0});
        adj[u].push_back(m);
        m++;
        edges.push_back({v, u, cap, cap});
        adj[v].push_back(m);
        m++;
    }

    int bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int e : adj[u]) {
                int v = edges[e].to;
                if (edges[e].cap - edges[e].f > 0 && level[v] == -1) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] != -1;
    }

    ll dfs(int u, ll pushed) {
        if (!pushed) {
            return 0;
        }
        if (u == t) {
            return pushed;
        }
        for (int &i = ptr[u]; i < adj[u].size(); i++) {
            int e = adj[u][i];
            int v = edges[e].to;
            if (edges[e].cap - edges[e].f == 0 || level[v] != level[u] + 1) {
                continue;
            }
            ll cur = dfs(v, min(pushed, edges[e].cap - edges[e].f));
            if (cur == 0) {
                continue;
            }
            pushed = cur;
            edges[e].f += pushed;
            edges[e ^ 1].f -= pushed;
            return pushed;
        }
        return 0;
    }

    ll flow() {
        ll f = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (1) {
                ll cur = dfs(s, INF);
                if (cur == 0) {
                    break;
                }
                f += cur;
            }
        }
        return f;
    }
};

const int N = 105;

string a[N], b[N];
int comp[N][N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (comp[i][j]) {
                continue;
            }
            k++;
            queue<pair<int, int>> q;
            q.push(make_pair(i, j));
            comp[i][j] = k;
            while (q.size()) {
                int x = q.front().first, y = q.front().second;
                q.pop();
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (abs(dx) + abs(dy) == 1 && x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && a[x + dx][y + dy] == a[x][y] && !comp[x + dx][y + dy]) {
                            comp[x + dx][y + dy] = k;
                            q.push(make_pair(x + dx, y + dy));
                        }
                    }
                }
            }
        }
    }
    vector<ll> zero(k + 1, 0), one(k + 1, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (b[i][j] == '0') {
                zero[comp[i][j]]++;
            } else {
                one[comp[i][j]]++;
            }
        }
    }
    Flow flow(k + 2, 0, k + 1);
    for (int i = 1; i <= k; i++) {
        flow.add_edge(0, i, zero[i]);
        flow.add_edge(i, k + 1, one[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '0') {
                continue;
            }
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dx) + abs(dy) == 1 && i + dx >= 0 && i + dx < n && j + dy >= 0 && j + dy < m && a[i + dx][j + dy] == '0') {
                        flow.add_edge(comp[i][j], comp[i + dx][j + dy], INF);
                    }
                }
            }
        }
    }
    cout << flow.flow();

    return 0;
}
