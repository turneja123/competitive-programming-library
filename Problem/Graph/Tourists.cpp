//https://codeforces.com/contest/487/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 19;
const int INF = 1e9;

int a[N];
int vis[N];
int low[N];
int depth[N];
int is_art[N];
vector<int> adj[N];
vector<int> vec;

vector<vector<int>> bicomps;

void dfs(int u) {
    vec.push_back(u);
    vis[u] = 1;
    low[u] = depth[u];
    int child = 0;
    for (int v : adj[u]) {
        if (!vis[v]) {
            child++;
            depth[v] = depth[u] + 1;
            dfs(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= depth[u]) {
                is_art[u] = 1;
                vector<int> cur;
                while (1) {
                    int w = vec.back();
                    cur.push_back(w);
                    vec.pop_back();
                    if (w == v) {
                        break;
                    }
                }
                cur.push_back(u);
                bicomps.push_back(cur);
            }
        } else if (depth[u] - depth[v] > 1) {
            low[u] = min(low[u], depth[v]);
        }
    }
    if (u == 0 && child < 2) {
        is_art[u] = 0;
    }
}

const int M = 2 * N;

int sz[M];
int id[M];
vector<int> adj_bct[M];
int head[M];
int depth_bct[M];
int up[K][M];
multiset<int> st[M];
int val[M];


int pos[M];
int id_hld[M];
vector<vector<int>> paths;

void dfs_sz(int u, int p, int spl) {
    sz[u] = 1;
    up[0][u] = p;
    if (u >= spl && u != p) {
        st[p].insert(val[u]);
    }

    for (int i = 1; i < K; i++) {
        int v = up[i - 1][u];
        up[i][u] = up[i - 1][v];
    }
    for (int v : adj_bct[u]) {
        if (v != p) {
            depth_bct[v] = depth_bct[u] + 1;
            dfs_sz(v, u, spl);
            sz[u] += sz[v];
        }
    }
}

vector<int> tour;
int timer = 0;

void dfs_hld(int u, int p) {
    tour.push_back(u);
    pos[u] = timer++;
    vector<int> child;
    for (int v : adj_bct[u]) {
        if (v != p) {
            child.push_back(v);
        }
    }
    if (child.empty()) {
        return;
    }
    sort(child.begin(), child.end(), [&](int a, int b) {return sz[a] > sz[b];});
    for (int v : child) {
        if (2 * sz[v] >= sz[u]) {
            head[v] = 0;
        }
        dfs_hld(v, u);
    }
}


int segtree[4 * M];

int rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return (int)1e9;
    }

    int mid = (l + r) / 2;
    return min(rmq(l, mid, lq, rq, 2 * node + 1),
               rmq(mid + 1, r, lq, rq, 2 * node + 2));
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
        segtree[node] = val[tour[l]];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = min(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int lca(int u, int v) {
    if (depth_bct[u] > depth_bct[v]) {
        swap(u, v);
    }
    int d = depth_bct[v] - depth_bct[u];
    for (int i = K - 1; i >= 0; i--) {
        int c = d & (1 << i);
        if (c) {
            v = up[i][v];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = K - 1; i >= 0; i--) {
        if (up[i][u] != up[i][v]) {
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][u];
}


int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0);
    if (adj[0].size() == 0) {
        bicomps.push_back({0});
    }

    int n_bct = bicomps.size();
    for (int i = 0; i < n; i++) {
        if (is_art[i]) {
            id[i] = n_bct++;
            val[id[i]] = a[i];
        }
    }

    for (int i = 0; i < bicomps.size(); i++) {
        for (int j : bicomps[i]) {
            if (!is_art[j]) {
                id[j] = i;
                st[i].insert(a[j]);
            }
            if (is_art[j]) {
                adj_bct[i].push_back(id[j]);
                adj_bct[id[j]].push_back(i);
            }
        }
    }
    for (int i = 0; i < n_bct; i++) {
        head[i] = 1;
    }
    dfs_sz(0, 0, bicomps.size());
    dfs_hld(0, 0);

    vector<int> ord(n_bct);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {return depth_bct[a] > depth_bct[b];});
    vector<int> vis(n_bct, 0);
    m = 0;
    for (int i = 0; i < n_bct; i++) {
        int u = ord[i];
        if (vis[u]) {
            continue;
        }
        vector<int> path;
        while (1) {
            vis[u] = 1;
            id_hld[u] = m;
            path.push_back(u);
            if (head[u]) {
                break;
            }
            u = up[0][u];
        }
        m++;
        paths.push_back(path);
    }
    for (int i = 0; i < bicomps.size(); i++) {
        val[i] = (st[i].empty() ? INF : *st[i].begin());
    }
    build(0, n_bct - 1, 0);
    for (int i = 0; i < q; i++) {
        char c;
        cin >> c;
        int u, v;
        cin >> u >> v;
        if (c == 'A') {
            u--, v--;

            if (u == v) {
                cout << a[u] << endl;
                continue;
            }
            int U = id[u], V = id[v];
            int anc = lca(U, V);
            if (U == V) {
                int ans = val[U];
                if (U < bicomps.size()) {
                    ans = min(ans, val[up[0][U]]);
                }
                cout << ans << endl;
                continue;
            }

            int ans = 1e9;
            auto query = [&](int u, int L) -> void {
                while (1) {
                    int j = id_hld[u];
                    int v = (id_hld[u] == id_hld[L] ? L : paths[j].back());

                    int l = pos[v], r = pos[u];
                    ans = min(ans, rmq(0, n_bct - 1, l, r, 0));

                    if (id_hld[u] == id_hld[L]) {
                        break;
                    }

                    u = up[0][v];
                }
            };
            if (U != anc) {
                query(U, anc);
            }
            if (V != anc) {
                query(V, anc);
            }
            if (anc < bicomps.size()) {
                ans = min(ans, val[up[0][anc]]);
            }
            cout << ans << endl;
        } else {
            u--;
            int U = id[u];
            if (!is_art[u]) {
                st[U].erase(st[U].find(a[u]));
                a[u] = v;
                st[U].insert(a[u]);
                val[U] = *st[U].begin();
                update(0, n_bct - 1, pos[U], val[U], 0);
            } else {
                if (up[0][U] != U) {
                    st[up[0][U]].erase(st[up[0][U]].find(a[u]));
                }
                a[u] = v;
                val[U] = v;
                update(0, n_bct - 1, pos[U], val[U], 0);
                if (up[0][U] != U) {
                    st[up[0][U]].insert(a[u]);
                    val[up[0][U]] = *st[up[0][U]].begin();
                    update(0, n_bct - 1, pos[up[0][U]], val[up[0][U]], 0);
                }
            }
        }
    }

    return 0;
}
