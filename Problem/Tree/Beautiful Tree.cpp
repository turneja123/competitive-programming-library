//https://codeforces.com/contest/1904/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 19;
const int INF = 1e9;

int timer = 0;
int euler = 0;
int tin[N];
int tout[N];
int pos[N];
int up[K][N];
vector<int> adj[N];
int sz[N];
int depth[N];
int tail[N];
bool head[N];
int edges[N];
int tour[N];

void dfs(int u, int p) {
    tin[u] = ++timer;
    up[0][u] = p;
    sz[u] = 1;
    for (int i = 1; i < K; i++) {
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    tout[u] = ++timer;
    return;
}

void dfs_markedges(int u, int p) {
    tour[euler] = u;
    pos[u] = euler++;
    int heavy = -1;
    for (int v : adj[u]) {
        if (v != p) {
            if (sz[v] >= sz[u] / 2 + sz[u] % 2) {
                edges[v] = 1;
                head[u] = false;
                heavy = v;
            } else {
                edges[v] = 0;
            }
        }
    }
    if (heavy != -1) {
        dfs_markedges(heavy, u);
    }
    for (int v : adj[u]) {
        if (v != p && v != heavy) {
            dfs_markedges(v, u);
        }
    }

}

int kth(int u, int k) {
    for (int i = K - 1; i >= 0; i--) {
        int c = (1 << i) & k;
        if (c) {
            u = up[i][u];
        }
    }
    return u;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int i = K - 1; i >= 0; --i) {
        if (!is_ancestor(up[i][u], v)) {
            u = up[i][u];
        }
    }
    return up[0][u];
}

int idx = 0;
int L[8 * N];
int R[8 * N];
int root[2];
int deg[8 * N];

vector<int> topo[8 * N];

void upd(int l, int r, int lq, int rq, int node, int f, int v) {
    if (l > rq || r < lq) {
        return;
    }

    if (lq <= l && rq >= r) {
        if (f == 0) {
            topo[v].push_back(node);
            deg[node]++;
        } else {
            topo[node].push_back(v);
            deg[v]++;
        }
        return;
    }



    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, L[node], f, v);
    upd(mid + 1, r, lq, rq, R[node], f, v);
}

void build(int l, int r, int node, int f) {
    if (l == r) {
        if (f == 0) {
            topo[node].push_back(l);
            deg[l]++;
        } else {
            topo[l].push_back(node);
            deg[node]++;
        }
        return;
    }

    int mid = (l + r) / 2;
    L[node] = idx;
    build(l, mid, idx++, f);
    R[node] = idx;
    build(mid + 1, r, idx++, f);
    if (f == 0) {
        topo[node].push_back(L[node]);
        topo[node].push_back(R[node]);
        deg[L[node]]++;
        deg[R[node]]++;
    } else {
        topo[L[node]].push_back(node);
        topo[R[node]].push_back(node);
        deg[node] += 2;
    }
}


void calc(int u, int par, int n, int f, int v) {
    v = pos[v];
    while (1) {
        if (tail[u] == tail[par]) {
            upd(0, n - 1, pos[par], pos[par] + depth[u] - depth[par], root[f], f, v);
            break;
        }
        upd(0, n - 1, pos[tail[u]], pos[tail[u]] + depth[u] - depth[tail[u]], root[f], f, v);
        u = up[0][tail[u]];
    }
    return;
}


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        head[i] = true;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    dfs_markedges(0, 0);
    idx = n;
    root[0] = idx++;
    build(0, n - 1, root[0], 0);
    root[1] = idx++;
    build(0, n - 1, root[1], 1);
    for (int i = 0; i < n; i++) {
        if (head[i]) {
            vector<int> path;
            int v = i;
            while (1) {
                path.push_back(v);
                if (edges[v] == 0) {
                    break;
                }
                v = up[0][v];
            }
            for (int u : path) {
                tail[u] = path.back();
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int f, u, v, c;
        cin >> f >> u >> v >> c;
        f--, u--, v--, c--;
        if (depth[u] > depth[v]) {
            swap(u, v);
        }
        int l = lca(u, v);

        if (is_ancestor(c, v)) {

            if (c != v) {
                int d = depth[v] - depth[c];
                int go = kth(v, d - 1);
                calc(v, go, n, f, c);
            }

            if (c != 0) {
                v = up[0][c];
                if (is_ancestor(l, v)) {
                    calc(v, l, n, f, c);
                }
            }
        } else {
            calc(v, l, n, f, c);
        }


        if (l != u) {
            int d = depth[u] - depth[l];
            l = kth(u, d - 1);
            if (is_ancestor(c, u)) {
                if (c != u) {
                    int d = depth[u] - depth[c];
                    int go = kth(u, d - 1);
                    calc(u, go, n, f, c);
                }
                if (c != 0) {
                    u = up[0][c];
                    if (is_ancestor(l, u)) {
                        calc(u, l, n, f, c);
                    }
                }
            } else {
                calc(u, l, n, f, c);
            }
        }
    }
    vector<int> inv_ans(n), ans(n, -1);
    queue<int> qu;
    qu.push(root[0]);
    int ptr = 0;
    while (qu.size()) {
        int u = qu.front();
        qu.pop();
        if (u < n) {
            ans[u] = ptr++;
        }
        for (auto v : topo[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                qu.push(v);
            }
        }
    }

    int ok = 1;
    for (int i = 0; i < n; i++) {
        if (ans[i] == -1) {
            ok = 0;
            break;
        }
        inv_ans[tour[i]] = ans[i];
    }
    if (!ok) {
        cout << -1;
    } else {
        for (int i = 0; i < n; i++) {
            cout << inv_ans[i] + 1 << " ";
        }
    }


    return 0;
}
