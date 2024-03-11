//solution for https://cses.fi/problemset/task/2134/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

struct chash {
    int operator()(pair<int, int> x) const { return x.first* 31 + x.second; }
};

vector<vector<int>> paths;
vector<int> tin, tout;
vector<vector<int>> up;
int timer = 0, lg;
list<int> adj[N];
int vals[N];
int parent[N];
int depth[N];
int sz[N];
int tail[N];
pair<int, int> pos[N];
bool head[N];
gp_hash_table<pair<int, int>, int, chash> edges;

int dfs(int v, int p, int ct) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (*it != p) {
            parent[*it] = v;
            depth[*it] = depth[v] + 1;
            ct += dfs(*it, v, 1);
        }
    }
    tout[v] = ++timer;
    return sz[v] = ct;
}

void dfs_markedges(int v, int p) {
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (*it != p) {
            if (sz[*it] >= sz[v] / 2 + sz[v] % 2) {
                edges[{v, *it}] = 1;
                head[v] = false;
            } else {
                edges[{v, *it}] = 0;
            }
            dfs_markedges(*it, v);
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

vector<int> seg[N];

void build(int j) {

    int n = paths[j].size();
    seg[j].resize(2 * n);

    for (int i = 0; i < n; i++) {
        seg[j][i + n] = vals[paths[j][i]];
    }
    for (int i = n - 1; i > 0; i--) {
        seg[j][i] = max(seg[j][2 * i], seg[j][2 * i + 1]);
    }
}

void update(int pos, int val, int j) {
    int n = paths[j].size();
    pos += n;
    seg[j][pos] = val;
    while (pos > 1) {
        pos /= 2;
        seg[j][pos] = max(seg[j][2 * pos], seg[j][2 * pos + 1]);
    }
}

int rmq(int l, int r, int j) {
    int n = paths[j].size();
    l += n;
    r += n;
    int mx = 0;
    while (l < r) {
        if (r % 2 == 1) {
            mx = max(mx, seg[j][--r]);
        }
        if (l % 2 == 1) {
            mx = max(mx, seg[j][l++]);
        }
        l /= 2;
        r /= 2;
    }
    return mx;
}

int calc(int a, int b) {
    int mx = 0;
    while (1) {
        int j = pos[a].first;
        if (j == pos[b].first) {
            mx = max(mx, rmq(pos[a].second, pos[b].second + 1, j));
            break;
        }
        mx = max(mx, rmq(pos[a].second, paths[j].size(), j));
        a = parent[tail[a]];
    }
    return mx;
}


int main() {
    IOS;
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
                if (v == 0) {
                    break;
                }
                if (edges[{parent[v], v}] == 0) {
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
        build(i);
    }
    for (int i = 0; i < q; i++) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 2) {
            u--, v--;
            if (depth[v] > depth[u]) {
                swap(u, v);
            }
            int l = lca(u, v);
            int ans = calc(u, l);
            if (v != l) {
                ans = max(ans, calc(v, l));
            }
            cout << ans << " ";

        } else {
            u--;
            update(pos[u].second, v, pos[u].first);
        }
    }
    return 0;
}
