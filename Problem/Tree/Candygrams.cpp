//https://dmoj.ca/problem/utso24p6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

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

vector<long long> segtree[N];
vector<int> lazy[N];

void compose(int parent, int child, int n) {
    lazy[n][child] += lazy[n][parent];
}

void apply(int node, int l, int r, int n) {
    segtree[n][node] += (long long)lazy[n][node] * (r - l + 1);
    if (l != r) {
        compose(node, 2 * node + 1, n);
        compose(node, 2 * node + 2, n);
    }
    lazy[n][node] = 0;
}

long long query(int l, int r, int lq, int rq, int node, int n) {
    if (l > rq || r < lq || lq > rq) {
        return 0;
    }
    apply(node, l, r, n);
    if (lq <= l && rq >= r) {
        return segtree[n][node];
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1, n) + query(mid + 1, r, lq, rq, 2 * node + 2, n);
}

void incUpdate(int l, int r, int lq, int rq, int node, int add, int n) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[n][node] += add;
        return;
    }
    apply(node, l, r, n);
    int mid = (l + r) / 2;
    incUpdate(l, mid, lq, rq, 2 * node + 1, add, n);
    incUpdate(mid + 1, r, lq, rq, 2 * node + 2, add, n);
    apply(2 * node + 1, l, mid, n);
    apply(2 * node + 2, mid + 1, r, n);
    segtree[n][node] = segtree[n][node * 2 + 1] + segtree[n][node * 2 + 2];
}



void upd(int a, int b, int k) {
    while (1) {
        int j = pos[a].first;
        if (j == pos[b].first) {
            incUpdate(0, paths[j].size() - 1, pos[a].second, pos[b].second, 0, k, j);
            break;
        }
        incUpdate(0, paths[j].size() - 1, pos[a].second, paths[j].size() - 1, 0, k, j);
        a = parent[tail[a]];
    }
    return;
}

long long calc(int a, int b, int flag) {
    long long s = 0;
    while (1) {
        int j = pos[a].first;
        if (j == pos[b].first) {
            s += query(0, paths[j].size() - 1, pos[a].second, pos[b].second - flag, 0, j);
            break;
        }
        s += query(0, paths[j].size() - 1, pos[a].second, paths[j].size() - 1, 0, j);
        a = parent[tail[a]];
    }
    return s;
}

int kth(int v, int k) {
    while (k > 0) {
        int l = log2(k);
        v = up[v][l];
        k ^= 1 << l;
    }
    return v;
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
        segtree[i].resize(4 * paths[i].size(), 0);
        lazy[i].resize(4 * paths[i].size(), 0);
    }
    long long total = 0;
    for (int i = 0; i < q; i++) {
        char c;
        cin >> c;
        if (c == 'U') {
            int x, k;
            cin >> x >> k;
            x--;
            upd(x, 0, k);
            total += k * depth[x];
        } else {
            int a, b;
            cin >> a >> b;
            a--, b--;
            if (depth[a] < depth[b]) {
                swap(a, b);
            }
            int diff = (depth[a] - depth[b] - 1);
            if (diff < 1) {
                cout << total << endl;
                continue;
            }
            if (diff == 1) {
                int j = pos[a].first;
                long long ans = total - query(0, paths[j].size() - 1, pos[a].second, pos[a].second, 0, j);
                cout << ans << endl;
                continue;
            }
            int high = diff / 2;
            int v = kth(a, high);
            long long ans = total - calc(a, v, 1) * 2;
            if (diff % 2 == 1) {
                int j = pos[v].first;
                ans -= query(0, paths[j].size() - 1, pos[v].second, pos[v].second, 0, j);
            }
            cout << ans << endl;
        }
    }
    return 0;
}
