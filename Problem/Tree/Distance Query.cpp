//https://www.spoj.com/problems/DISQUERY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

vector<vector<int>> paths;
vector<int> tin, tout;
vector<vector<int>> up;
int timer = 0, lg;
vector<pair<int, int>> adj[N];
int vals[N];
int parent[N];
int sz[N];
int tail[N];
pair<int, int> pos[N];
bool head[N];
int edges[N];

int dfs(int v, int p, int ct) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (pair<int, int> pr : adj[v]) {
        int u = pr.first;
        if (u != p) {
            vals[u] = pr.second;
            parent[u] = v;
            ct += dfs(u, v, 1);
        }
    }
    tout[v] = ++timer;
    return sz[v] = ct;
}

void dfs_markedges(int v, int p) {
    for (pair<int, int> pr : adj[v]) {
        int u = pr.first;
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

vector<pair<int, int>> segtree[N];

pair<int, int> rmq(int l, int r, int lq, int rq, int node, int n) {
    if (l > rq || r < lq || lq > rq) {
        return make_pair(INF, 0);
    }

    if (lq <= l && rq >= r) {
        return segtree[n][node];
    }

    int mid = (l + r) / 2;
    pair<int, int> ln = rmq(l, mid, lq, rq, 2 * node + 1, n);
    pair<int, int> rn = rmq(mid + 1, r, lq, rq, 2 * node + 2, n);
    return make_pair(min(ln.first, rn.first), max(ln.second, rn.second));
}

void build(int l, int r, int node, int n) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[n][node].first = vals[paths[n][l]];
        segtree[n][node].second = vals[paths[n][l]];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, n);
    build(mid + 1, r, 2 * node + 2, n);
    segtree[n][node].first = min(segtree[n][2 * node + 1].first, segtree[n][2 * node + 2].first);
    segtree[n][node].second = max(segtree[n][2 * node + 1].second, segtree[n][2 * node + 2].second);
}

pair<int, int> calc(int a, int b, int flag) {
    int mx = 0, mn = INF;
    while (1) {
        int j = pos[a].first;
        if (j == pos[b].first) {
            pair<int, int> p = rmq(0, paths[j].size() - 1, pos[a].second, pos[b].second - flag, 0, j);
            mn = min(mn, p.first);
            mx = max(mx, p.second);
            break;
        }
        pair<int, int> p = rmq(0, paths[j].size() - 1, pos[a].second, paths[j].size() - 1, 0, j);
        mn = min(mn, p.first);
        mx = max(mx, p.second);
        a = parent[tail[a]];
    }
    return make_pair(mn, mx);;
}


int main() {
    IOS;
    int n, q;
    cin >> n;
    lg = ceil(log2(n));
    up.assign(n, vector<int>(lg + 1));
    tin.resize(n);
    tout.resize(n);
    for (int i = 0; i < n; i++) {
        head[i] = true;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
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
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (tin[u] > tin[v]) {
            swap(u, v);
        }
        int l = lca(u, v);
        pair<int, int> ans = calc(v, l, 1);
        if (u != l) {
            pair<int, int> p = calc(u, l, 1);
            ans.first = min(ans.first, p.first);
            ans.second = max(ans.second, p.second);
        }
        cout << ans.first << " " << ans.second << endl;;


    }
    return 0;
}
