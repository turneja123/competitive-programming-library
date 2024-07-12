//https://www.codechef.com/problems/QRYLAND
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

const long long M = 1e9 + 7;
const long long P = 26, Q = 53;

vector<vector<int>> paths;
vector<int> tin, tout;
vector<vector<int>> up;
int timer = 0, lg;
vector<int> adj[N];
int vals[N];
int parent[N];
int sz[N];
int tail[N];
pair<int, int> pos[N];
bool head[N];
int edges[N];
int depth[N];
pair<long long, long long> perm[N];

int dfs(int v, int p, int ct) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : adj[v]) {
        if (u != p) {
            parent[u] = v;
            depth[u] = depth[v] + 1;
            ct += dfs(u, v, 1);
        }
    }
    tout[v] = ++timer;
    return sz[v] = ct;
}

void dfs_markedges(int v, int p) {
    for (int u : adj[v]) {
        if (u != p) {
            if (sz[u] >= sz[v] / 2 + sz[v] % 2) {
                edges[u] = 1;
                head[v] = false;
            } else {
                edges[u] = 0;
            }
            dfs_markedges(u, v);
        }
    }
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
    for (int i = lg; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

vector<pair<long long, long long>> segtree[N];

pair<long long, long long> prod(int l, int r, int lq, int rq, int node, int n) {
    if (lq <= l && rq >= r) {
        return make_pair(segtree[n][node].first, segtree[n][node].second);
    }

    if (l > rq || r < lq) {
        return make_pair(1, 1);
    }

    int mid = (l + r) / 2;
    pair<long long, long long> lf = prod(l, mid, lq, rq, 2 * node + 1, n);
    pair<long long, long long> rt = prod(mid + 1, r, lq, rq, 2 * node + 2, n);

    return make_pair(lf.first * rt.first % M, lf.second * rt.second % M);
}

void update(int l, int r, int ind, long long val, int node, int n) {
    if (l == r) {
        segtree[n][node].first = P + val;
        segtree[n][node].second = Q + val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1, n);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2, n);
    }
    segtree[n][node].first = segtree[n][2 * node + 1].first * segtree[n][2 * node + 2].first % M;
    segtree[n][node].second = segtree[n][2 * node + 1].second * segtree[n][2 * node + 2].second % M;
}


void build(int l, int r, int node, int n) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[n][node].first = P + vals[paths[n][l]];
        segtree[n][node].second = Q + vals[paths[n][l]];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, n);
    build(mid + 1, r, 2 * node + 2, n);
    segtree[n][node].first = segtree[n][2 * node + 1].first * segtree[n][2 * node + 2].first % M;
    segtree[n][node].second = segtree[n][2 * node + 1].second * segtree[n][2 * node + 2].second % M;

}

pair<long long, long long> calc(int a, int b, int flag) {
    pair<long long, long long> ans = make_pair(1, 1);
    while (1) {
        int j = pos[a].first;
        if (j == pos[b].first) {
            pair<long long, long long> path_prod = prod(0, paths[j].size() - 1, pos[a].second, pos[b].second - flag, 0, j);
            ans.first = ans.first * path_prod.first % M;
            ans.second = ans.second * path_prod.second % M;
            break;
        }
        pair<long long, long long> path_prod = prod(0, paths[j].size() - 1, pos[a].second, paths[j].size() - 1, 0, j);
        ans.first = ans.first * path_prod.first % M;
        ans.second = ans.second * path_prod.second % M;
        a = parent[tail[a]];
    }
    return ans;
}


int main() {
    IOS;
    perm[0] = make_pair(1, 1);
    for (int i = 1; i < N; i++) {
        perm[i].first = perm[i - 1].first * (P + i) % M;
        perm[i].second = perm[i - 1].second * (Q + i) % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        lg = ceil(log2(n));
        up.assign(n, vector<int>(lg + 1));
        tin.resize(n);
        tout.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> vals[i];
            head[i] = true;
        }

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, 0, 1);
        dfs_markedges(0, 0);
        for (int i = 0; i < n; i++) {
            if (head[i]) {
                vector<int> path;
                int v = i;
                while (1) {
                    path.push_back(v);
                    if (edges[v] == 0) {
                        break;
                    }
                    v = parent[v];
                }
                for (int i = 0; i < path.size(); i++) {
                    tail[path[i]] = path[path.size() - 1];
                    pos[path[i]] = {paths.size(), i};
                }
                paths.push_back(path);
            }
        }

        for (int i = 0; i < paths.size(); i++) {
            segtree[i].resize(4 * paths[i].size());
            build(0, paths[i].size() - 1, 0, i);
        }
        for (int i = 0; i < q; i++) {
            int t, u, v;
            cin >> t >> u >> v;
            if (t == 1) {
                u--, v--;
                if (tin[u] > tin[v]) {
                    swap(u, v);
                }
                int l = lca(u, v);
                pair<long long, long long> ans = calc(v, l, 0);
                if (u != l) {
                    pair<long long, long long> p = calc(u, l, 1);
                    ans.first = ans.first * p.first % M;
                    ans.second = ans.second * p.second % M;
                }
                int len = depth[u] + depth[v] - 2 * depth[l] + 1;

                if (perm[len] == ans) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }

            } else {
                u--;
                int j = pos[u].first;
                update(0, paths[j].size() - 1, pos[u].second, v, 0, j);
            }
        }
        for (int i = 0; i < n; i++) {
            segtree[i].clear();
            adj[i].clear();
        }
        tin.clear();
        tout.clear();
        up.clear();
    }
    return 0;
}
