//https://dmoj.ca/problem/lct
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

struct Bcc {
    vector<int> nodes;
    vector<int> queries;
};

Bcc bcc[N];

int id, idx, tim, m, e;
int tim_x, tim_y;
vector<tuple<int, int, int>> queries;
vector<pair<int, int>> adj[N];
vector<int> rev[N];
vector<int> tok[N];
vector<int> valid;

int take[N];
int deg[N];
int vis[N];
int inq[N];
int par[N];
int ord[N];
int parent[N];
int disc[N], low[N];
int seen[N], c[N], seen_comp[N];
int need[N];

struct Edge {
    int u;
    int v;
    int e;
    Edge(int u, int v, int e) : u(u), v(v), e(e) {}
    bool operator == (const Edge &a) const { return u == a.u && v == a.v && e == a.e; }
};

vector<Edge> st;

void add_edge(int u, int v) {
    adj[u].push_back({v, e});
    adj[v].push_back({u, e});
    rev[u].push_back(v);
    deg[v]++;
    e++;
}

void push(int u) {
    if (vis[u] || inq[u] || deg[u] || need[u]) {
        return;
    }
    inq[u] = 1;
    valid.push_back(u);
}

int check(int u, int v) {
    if (tok[u].size() > tok[v].size()) {
        swap(u, v);
    }
    tim_x++;
    for (int id : tok[u]) {
        seen[id] = tim_x;
    }
    for (int id : tok[v]) {
        if (seen[id] == tim_x) {
            return id;
        }
    }
    return 0;
}

vector<vector<int>> bicomps;

void dfs(int u, int p, int root) {
    tim++;
    disc[u] = tim;
    low[u] = tim;
    int child = 0;
    for (auto [v, e] : adj[u]) {
        if (vis[v] || !take[v] || e == p) {
            continue;
        }
        if (!disc[v]) {
            st.push_back({u, v, e});
            child++;
            dfs(v, e, root);
            low[u] = min(low[u], low[v]);
            if ((u != root && low[v] >= disc[u]) || (u == root && child > 1)) {
                vector<int> cur;
                while (!(st.back() == Edge(u, v, e))) {
                    cur.push_back(st.back().u);
                    cur.push_back(st.back().v);
                    st.pop_back();
                }
                cur.push_back(st.back().u);
                cur.push_back(st.back().v);
                st.pop_back();
                bicomps.push_back(cur);
            }
        } else if (disc[v] < disc[u]) {
            low[u] = min(low[u], disc[v]);
            st.push_back({u, v, e});
        }
    }
}

void build(int n, int q) {
    for (int u = 0; u < n; u++) {
        if (!disc[u]) {
            st.clear();
            dfs(u, -1, u);
            vector<int> cur;
            while (st.size()) {
                cur.push_back(st.back().u);
                cur.push_back(st.back().v);
                st.pop_back();
            }
            if (cur.size()) {
                bicomps.push_back(cur);
            }
            for (auto &nodes : bicomps) {
                if (nodes.empty()) {
                    continue;
                }
                idx++, id++;
                for (int x : nodes) {
                    if (seen_comp[x] != id) {
                        seen_comp[x] = id;
                        bcc[idx].nodes.push_back(x);
                        tok[x].push_back(idx);
                    }
                }
            }
            bicomps.clear();
        }
    }

    for (int i = 0; i < q; i++) {
        auto [u, v, w] = queries[i];
        if (u == w || v == w) {
            continue;
        }
        int id = check(u, v);
        if (!id) {
            need[w]--;
        } else {
            bcc[id].queries.push_back(i);
        }
    }

    for (int i = 0; i < n; i++) {
        push(i);
    }
    for (int i = 0; i < n; i++) {
        disc[i] = 0;
        low[i] = 0;
        take[i] = 0;
    }
}

void calc() {
    vector<int> cur = valid;
    valid.clear();
    for (int u : cur) {
        inq[u] = 0;
    }

    for (int u : cur) {
        vis[u] = 1;
        ord[m++] = u;
        for (int v : rev[u]) {
            deg[v]--;
            push(v);
        }
    }

    vector<int> comp, nodes;
    tim_x++;
    for (int u : cur) {
        for (int id : tok[u]) {
            if (seen[id] != tim_x) {
                seen[id] = tim_x;
                comp.push_back(id);
            }
        }
    }

    tim_y++;
    for (int id : comp) {
        for (int u : bcc[id].nodes) {
            if (vis[u] || c[u] == tim_y) {
                continue;
            }
            c[u] = tim_y;
            nodes.push_back(u);
            take[u] = 1;
        }
    }

    for (int u : nodes) {
        vector<int> keep;
        for (int id : tok[u]) {
            if (seen[id] != tim_x) {
                keep.push_back(id);
            }
        }
        tok[u] = keep;
    }

    for (int u : nodes) {
        if (!disc[u]) {
            st.clear();
            dfs(u, -1, u);
            vector<int> cur;
            while (st.size()) {
                cur.push_back(st.back().u);
                cur.push_back(st.back().v);
                st.pop_back();
            }
            if (cur.size()) {
                bicomps.push_back(cur);
            }
            for (auto &nodes : bicomps) {
                if (nodes.empty()) {
                    continue;
                }
                idx++, id++;
                for (int x : nodes) {
                    if (seen_comp[x] != id) {
                        seen_comp[x] = id;
                        bcc[idx].nodes.push_back(x);
                        tok[x].push_back(idx);
                    }
                }
            }
            bicomps.clear();
        }
    }

    for (int id : comp) {
        for (int j : bcc[id].queries) {
            auto [u, v, w] = queries[j];
            int nw = check(u, v);
            if (!nw) {
                need[w]--;
                push(w);
            } else {
                bcc[nw].queries.push_back(j);
            }
        }
    }

    for (int id : comp) {
        bcc[id].nodes.clear();
        bcc[id].queries.clear();
    }
    for (int u : nodes) {
        disc[u] = 0;
        low[u] = 0;
        take[u] = 0;
    }
    for (int u : cur) {
        tok[u].clear();
    }
}

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int x, int y) {
    y = dsu_find(y);
    if (y != x) {
        parent[y] = x;
    }
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    queries.resize(q);
    for (int i = 0; i < q; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--, w--;
        queries[i] = {u, v, w};
        if (u != w && v != w) {
            need[w]++;
        }
        if (u != w) {
            add_edge(w, u);
        }
        if (v != w) {
            add_edge(w, v);
        }
    }
    for (int i = 0; i < n; i++) {
        par[i] = -1;
        parent[i] = i;
        take[i] = 1;
    }

    build(n, q);
    while (m < n) {
        if (valid.empty()) {
            break;
        }
        calc();
    }

    for (int i = m - 1; i >= 0; i--) {
        int u = ord[i];
        for (int v : rev[u]) {
            par[dsu_find(v)] = u;
        }
        for (int v : rev[u]) {
            dsu_unite(u, v);
        }
    }

    for (int i = 1; i < n; i++) {
        if (par[i] == -1) {
            par[i] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << par[i] + 1 << " ";
    }
    return 0;
}
