//https://dmoj.ca/problem/ioi18p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int INF = 1e9;
const int K = 21;

struct KRT {
    int parent[N];
    int tin[N];
    int up[K][N];
    int val[N];
    int sz[N];
    int tour[N];
    int L[N];
    int R[N];
    int timer = 0;
    int n;
    int e;
    int segtree[4 * N];

    vector<int> adj[N];

    KRT(int m) {
        e = m;
        n = m;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            val[i] = i;
        }
    }

    int dsu_find(int u) {
        if (parent[u] == u) {
            return u;
        }
        return parent[u] = dsu_find(parent[u]);
    }

    void add_edge(int u, int v, int wt) {
        u = dsu_find(u), v = dsu_find(v);
        if (u == v) {
            return;
        }
        val[e] = wt;
        parent[u] = e;
        parent[v] = e;
        parent[e] = e;
        adj[e].push_back(v);
        adj[e].push_back(u);
        adj[u].push_back(e);
        adj[v].push_back(e);
        e++;
        return;
    }

    void dfs(int u, int p) {
        tour[timer] = val[u];
        tin[u] = timer++;
        up[0][u] = p;
        L[u] = INF;
        R[u] = -INF;
        for (int k = 1; k < K; k++) {
            up[k][u] = up[k - 1][up[k - 1][u]];
        }
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
                L[u] = min(L[u], L[v]);
                R[u] = max(R[u], R[v]);
            }
        }
        if (u < n) {
            L[u] = tin[u];
            R[u] = tin[u];
        }
    }

    int rmq(int l, int r, int lq, int rq, int node) {
        if (lq <= l && rq >= r) {
            return segtree[node];
        }

        if (l > rq || r < lq) {
            return INF;
        }

        int mid = (l + r) / 2;
        return min(rmq(l, mid, lq, rq, 2 * node + 1), rmq(mid + 1, r, lq, rq, 2 * node + 2));
    }

    void update(int l, int r, int ind, int val, int node) {
        if (l == r) {
            segtree[node] = val;
            return;
        }

        int mid = (l + r) / 2;
        if (ind >= l && ind <= mid) {
            update(l, mid, ind, val, 2 * node + 1);
        } else {
            update(mid + 1, r, ind, val, 2 * node + 2);
        }
        segtree[node] = min(segtree[2 * node + 1], segtree[2 * node + 2]);
    }


    void build(int l, int r, int node) {
        if (l > r) {
            return;
        }
        if (l == r) {
            segtree[node] = INF;
            return;
        }

        int mid = (l + r) / 2;
        build(l, mid, 2 * node + 1);
        build(mid + 1, r, 2 * node + 2);
        segtree[node] = min(segtree[2 * node + 1], segtree[2 * node + 2]);
    }

};

std::vector<int> check_validity(int N, std::vector<int> X, std::vector<int> Y, std::vector<int> S, std::vector<int> E, std::vector<int> L, std::vector<int> R) {
    vector<int> ans;
    int n = N;
    KRT kmx(n);
    KRT kmn(n);
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < X.size(); i++) {
        edges.push_back(make_tuple(max(X[i], Y[i]), X[i], Y[i]));
    }
    sort(edges.begin(), edges.end());
    for (auto [wt, u, v] : edges) {
        kmn.add_edge(u, v, wt);
    }
    edges.clear();
    for (int i = 0; i < X.size(); i++) {
        edges.push_back(make_tuple(min(X[i], Y[i]), X[i], Y[i]));
    }
    sort(edges.begin(), edges.end());
    reverse(edges.begin(), edges.end());
    for (auto [wt, u, v] : edges) {
        kmx.add_edge(u, v, wt);
    }
    int root = kmx.dsu_find(0);
    kmx.dfs(root, root);
    root = kmn.dsu_find(0);
    kmn.dfs(root, root);
    int nmx = kmx.e, nmn = kmn.e;
    vector<tuple<int, int, int, int, int, int, int>> queries;
    int Q = S.size();
    for (int i = 0; i < Q; i++) {
        int u = E[i];
        for (int k = K - 1; k >= 0; k--) {
            if (kmn.val[kmn.up[k][u]] <= R[i]) {
                u = kmn.up[k][u];
            }
        }
        int l = kmn.L[u], r = kmn.R[u];
        queries.push_back(make_tuple(l, r, S[i], E[i], L[i], R[i], i));
    }
    sort(queries.begin(), queries.end());
    kmx.build(0, nmx - 1, 0);
    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < n; i++) {
        kmx.update(0, nmx - 1, kmx.tin[i], kmn.tin[i], 0);
        pq.push({-kmn.tin[i], i});
    }
    ans.resize(Q);
    for (auto [l, r, S, E, L, R, j] : queries) {
        while (pq.size() && -pq.top().first < l) {
            auto [_, i] = pq.top();
            pq.pop();
            kmx.update(0, nmx - 1, kmx.tin[i], INF, 0);
        }
        int u = S;
        for (int k = K - 1; k >= 0; k--) {
            if (kmx.val[kmx.up[k][u]] >= L) {
                u = kmx.up[k][u];
            }
        }
        int f = kmx.rmq(0, nmx - 1, kmx.L[u], kmx.R[u], 0);
        if (f <= r) {
            ans[j] = 1;
        } else {
            ans[j] = 0;
        }
    }
    return ans;
}
int main() {
    IOS;
    return 0;
}
