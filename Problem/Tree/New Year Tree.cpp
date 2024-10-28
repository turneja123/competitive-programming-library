//https://tlx.toki.id/problems/troc-18/E/
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
vector<int> adj[N];
int vals[N];
int parent[N];
int sz[N];
int tail[N];
pair<int, int> pos[N];
bool head[N];
int edges[N];

int sz_paths[N];
int pos_tour[N];
int path_pos[N];

vector<int> paths_tour;

int dfs(int v, int p, int ct) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : adj[v]) {
        if (u != p) {
            parent[u] = v;
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

void dfs_paths(int v, int p) {
    pos_tour[v] = paths_tour.size();
    int j = pos[v].first;
    if (pos[v].second == paths[j].size() - 1) {
        path_pos[j] = paths_tour.size();
        paths_tour.push_back(j);
        sz_paths[v]++;
    }
    for (int u : adj[v]) {
        if (u != p) {
            dfs_paths(u, v);
            sz_paths[v] += sz_paths[u];
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

int segtree_paths[4 * N];
int lazy_paths[4 * N];

void compose_paths(int parent, int child) {
    lazy_paths[child] ^= lazy_paths[parent];
}

void apply_paths(int node, int l, int r) {
    if ((r - l + 1) % 2 == 1) {
        segtree_paths[node] ^= lazy_paths[node];
    }
    if (l != r) {
        compose_paths(node, 2 * node + 1);
        compose_paths(node, 2 * node + 2);
    }
    lazy_paths[node] = 0;
}

void incUpdate_paths(int node, int l, int r, int lq, int rq, int add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy_paths[node] ^= add;
        return;
    }
    apply_paths(node, l, r);
    int mid = (l + r) / 2;
    incUpdate_paths(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate_paths(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply_paths(2 * node + 1, l, mid);
    apply_paths(2 * node + 2, mid + 1, r);
    segtree_paths[node] = segtree_paths[node * 2 + 1] ^ segtree_paths[node * 2 + 2]; //nebitno
}

int getXor_paths(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply_paths(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree_paths[node];
    }
    int mid = (l + r) / 2;
    return max(getXor_paths(l, mid, lq, rq, 2 * node + 1),
           getXor_paths(mid + 1, r, lq, rq, 2 * node + 2));
}

vector<int> segtree[N];
vector<int> lazy[N];

void compose(int parent, int child, int n) {
    lazy[n][child] ^= lazy[n][parent];
}

void apply(int node, int l, int r, int n) {
    if ((r - l + 1) % 2 == 1) {
        segtree[n][node] ^= lazy[n][node];
    }
    if (l != r) {
        compose(node, 2 * node + 1, n);
        compose(node, 2 * node + 2, n);
    }
    lazy[n][node] = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, int add, int n) {
    if (l > rq || lq > r || lq > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[n][node] ^= add;
        return;
    }
    apply(node, l, r, n);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add, n);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add, n);
    apply(2 * node + 1, l, mid, n);
    apply(2 * node + 2, mid + 1, r, n);
    segtree[n][node] = segtree[n][2 * node + 1] ^ segtree[n][2 * node + 2];
}

int getXor(int l, int r, int lq, int rq, int node, int n) {
    if (l > rq || lq > r || lq > rq) {
        return 0;
    }
    apply(node, l, r, n);
    if (l >= lq && r <= rq) {
        return segtree[n][node];
    }
    int mid = (l + r) / 2;
    return getXor(l, mid, lq, rq, 2 * node + 1, n) ^
           getXor(mid + 1, r, lq, rq, 2 * node + 2, n);
}

void build(int l, int r, int node, int n) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[n][node] = 0;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, n);
    build(mid + 1, r, 2 * node + 2, n);
    segtree[n][node] = segtree[n][2 * node + 1] ^ segtree[n][2 * node + 2];
}

int calc(int a, int b, int flag) {
    int ans = 0;
    while (1) {
        int j = pos[a].first;
        if (j == pos[b].first) {
            ans ^= getXor(0, paths[j].size() - 1, pos[a].second, pos[b].second - flag, 0, j);
            if ((pos[b].second - flag - pos[a].second + 1) % 2 == 1) {
                ans ^= getXor_paths(0, paths.size() - 1, path_pos[j], path_pos[j], 0);
            }
            break;
        }
        ans ^= getXor(0, paths[j].size() - 1, pos[a].second, paths[j].size() - 1, 0, j);
        if ((paths[j].size() - 1 - pos[a].second + 1) % 2 == 1) {
            ans ^= getXor_paths(0, paths.size() - 1, path_pos[j], path_pos[j], 0);
        }
        a = parent[tail[a]];
    }
    return ans;
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
        lazy[i].resize(4 * paths[i].size());
        segtree[i].resize(4 * paths[i].size());
        build(0, paths[i].size() - 1, 0, i);
    }
    dfs_paths(0, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t, u, v;
        cin >> t;
        if (t == 2) {
            cin >> u;
            u--;
            int ans = calc(u, 0, 0);
            cout << ans << endl;

        } else {
            cin >> u >> v;
            u--;
            if (sz_paths[u] != 0) {
                incUpdate_paths(0, 0, paths.size() - 1, pos_tour[u], pos_tour[u] + sz_paths[u] - 1, v);
            }
            int j = pos[u].first;
            if (pos[u].second != paths[j].size() - 1) {
                incUpdate(0, 0, paths[j].size() - 1, 0, pos[u].second, v, j);
            }
        }
    }
    return 0;
}
