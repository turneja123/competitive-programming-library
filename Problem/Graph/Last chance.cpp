//https://codeforces.com/contest/1045/problem/A
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

const int N = 5005;

int id_n[4 * N];
int id_w[N];

int who[4 * N];
int inv_who[4 * N];

int idx = 1;

void build(int l, int r, int node) {
    id_n[node] = idx++;
    if (l == r) {
        who[id_n[node]] = l + 1;
        inv_who[l] = node;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
}

void add(int l, int r, int node, int lq, int rq, int id, Flow &flow) {
    if (lq > r || rq < l) {
        return;
    }
    if (l >= lq && r <= rq) {
        flow.add_edge(id, id_n[node], 1);
        return;
    }
    int mid = (l + r) / 2;
    add(l, mid, 2 * node + 1, lq, rq, id, flow);
    add(mid + 1, r, 2 * node + 2, lq, rq, id, flow);

}

void build_flow(int l, int r, int node, Flow &flow) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    flow.add_edge(id_n[node], id_n[2 * node + 1], INF);
    flow.add_edge(id_n[node], id_n[2 * node + 2], INF);
    build_flow(l, mid, 2 * node + 1, flow);
    build_flow(mid + 1, r, 2 * node + 2, flow);
}

int main() {
    IOS;
    int n, m;
    cin >> m >> n;
    build(0, n - 1, 0);

    vector<tuple<int, int, int, vector<int>>> w;
    for (int i = 0; i < m; i++) {
        id_w[i] = idx++;
        int t;
        cin >> t;
        if (t == 0) {
            int k;
            cin >> k;
            vector<int> cur;
            for (int j = 0; j < k; j++) {
                int u;
                cin >> u;
                u--;
                cur.push_back(u);
            }
            w.push_back({0, -1, -1, cur});
        } else if (t == 2) {
            int k = 3;
            vector<int> cur;
            for (int j = 0; j < k; j++) {
                int u;
                cin >> u;
                u--;
                cur.push_back(u);
            }
            w.push_back({2, -1, -1, cur});
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            vector<int> cur;
            w.push_back({1, l, r, cur});
        }
    }
    idx++;
    Flow flow = Flow(idx, 0, idx - 1);
    build_flow(0, n - 1, 0, flow);
    for (int i = 0; i < m; i++) {
        auto [t, l, r, cur] = w[i];

        if (t == 0) {
            flow.add_edge(0, id_w[i], 1);
            for (int j : cur) {
                int u = inv_who[j];
                flow.add_edge(id_w[i], id_n[u], 1);
            }
        } else if (t == 2) {
            flow.add_edge(0, id_w[i], 2);
            for (int j : cur) {
                int u = inv_who[j];
                flow.add_edge(id_w[i], id_n[u], 1);
            }
        } else {
            flow.add_edge(0, id_w[i], 1);
            add(0, n - 1, 0, l, r, id_w[i], flow);
        }
    }
    for (int i = 0; i < n; i++) {
        int u = inv_who[i];
        flow.add_edge(id_n[u], idx - 1, 1);
    }
    cout << flow.flow() << endl;

    vector<int> who_destroyed_me(n, -1);
    vector<int> ct(m, 0);

    vector<pair<int, int>> par(idx);

    for (int i = 0; i < m; i++) {
        int u = id_w[i], t = get<0>(w[i]);
        int cur = 0;

        while (1) {
            if (t != 2 && cur == 1) {
                break;
            }
            if (cur == 2) {
                break;
            }
            queue<int> q;
            q.push(u);
            int V = -1;
            while (q.size()) {
                int u = q.front();
                q.pop();
                if (who[u]) {
                    V = u;
                    break;
                }
                for (int e : flow.adj[u]) {
                    if (e % 2 != 0 || flow.edges[e].f == 0) {
                        continue;
                    }
                    int v = flow.edges[e].to;
                    par[v] = {e, u};
                    q.push(flow.edges[e].to);
                }
            }
            if (V == -1) {
                break;
            }
            who_destroyed_me[who[V] - 1] = i;
            ct[i]++;
            while (V != u) {
                auto [e, p] = par[V];
                flow.edges[e].f--;
                V = p;
            }
            cur++;
        }
    }
    for (int i = 0; i < m; i++) {
        auto [t, l, r, cur] = w[i];
        if (t == 2 && ct[i] == 1) {
            for (int j : cur) {
                if (who_destroyed_me[j] != i) {
                    who_destroyed_me[j] = i;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (who_destroyed_me[i] != -1) {
            cout << who_destroyed_me[i] + 1 << " " << i + 1 << endl;
        }
    }

    return 0;
}
