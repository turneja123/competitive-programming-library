//https://www.spoj.com/problems/VZLA2019H/
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

const int N = 10005;
const int K = 1005;

ll pref[10][N];
ll h[10][K];

int id_n[10][4 * K];
int id_w[K];

int idx = 1;

void build(int l, int r, int node, int i) {
    id_n[i][node] = idx++;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, i);
    build(mid + 1, r, 2 * node + 2, i);
}

void add(int l, int r, int node, int lq, int rq, int id, int i, Flow &flow) {
    if (lq > r || rq < l) {
        return;
    }
    if (l >= lq && r <= rq) {
        flow.add_edge(id, id_n[i][node], INF);
        return;
    }
    int mid = (l + r) / 2;
    add(l, mid, 2 * node + 1, lq, rq, id, i, flow);
    add(mid + 1, r, 2 * node + 2, lq, rq, id, i, flow);
}

void build_flow(int l, int r, int node, int i, Flow &flow) {
    if (l == r) {
        flow.add_edge(id_n[i][node], flow.t, h[i][l]);
        return;
    }
    int mid = (l + r) / 2;
    flow.add_edge(id_n[i][node], id_n[i][2 * node + 1], INF);
    flow.add_edge(id_n[i][node], id_n[i][2 * node + 2], INF);
    build_flow(l, mid, 2 * node + 1, i, flow);
    build_flow(mid + 1, r, 2 * node + 2, i, flow);
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> pref[i][j];
            pref[i][j] += pref[i][j - 1];
        }
    }
    int q;
    cin >> q;
    vector<tuple<int, int, int, int, int>> w;
    vector<int> b;
    ll sum = 0;
    for (int i = 0; i < q; i++) {
        int r1, c1, r2, c2, p;
        cin >> r1 >> c1 >> r2 >> c2 >> p;
        r1--, r2--;
        w.push_back({r1, c1, r2, c2, p});
        b.push_back(c1);
        b.push_back(c2 + 1);
        sum += p;
    }
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int k = b.size() - 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            h[i][j] = pref[i][b[j + 1] - 1] - pref[i][b[j] - 1];
        }
        build(0, k - 1, 0, i);
    }
    for (int i = 0; i < q; i++) {
        id_w[i] = idx++;
    }
    idx++;
    Flow flow = Flow(idx, 0, idx - 1);
    for (int i = 0; i < n; i++) {
        build_flow(0, k - 1, 0, i, flow);
    }
    for (int i = 0; i < q; i++) {
        auto [r1, c1, r2, c2, p] = w[i];
        int l = lower_bound(b.begin(), b.end(), c1) - b.begin();
        int r = lower_bound(b.begin(), b.end(), c2 + 1) - b.begin() - 1;
        flow.add_edge(0, id_w[i], p);
        for (int j = r1; j <= r2; j++) {
            add(0, k - 1, 0, l, r, id_w[i], j, flow);
        }
    }
    if (flow.flow() == sum) {
        cout << "ugh" << endl;
    } else {
        cout << "BOOM!" << endl;
    }
    return 0;
}
