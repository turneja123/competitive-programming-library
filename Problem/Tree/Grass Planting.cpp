//https://www.spoj.com/problems/GRASSPLA/
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
vector<long long> lazy[N];

void compose(int parent, int child, int n) {
    lazy[n][child] += lazy[n][parent];
}

void apply(int node, int l, int r, int n) {
    segtree[n][node] += (r - l + 1) * lazy[n][node];
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
        lazy[n][node] += add;
        return;
    }
    apply(node, l, r, n);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add, n);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add, n);
    apply(2 * node + 1, l, mid, n);
    apply(2 * node + 2, mid + 1, r, n);
    segtree[n][node] = segtree[n][node * 2 + 1] + segtree[n][node * 2 + 2];
}

long long getSum(int l, int r, int lq, int rq, int node, int n) {
    if (l > rq || lq > r || lq > rq) {
        return 0;
    }
    apply(node, l, r, n);
    if (l >= lq && r <= rq) {
        return segtree[n][node];
    }
    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1, n) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2, n);
}

void build(int l, int r, int node, int n) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[n][node] = vals[paths[n][l]];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, n);
    build(mid + 1, r, 2 * node + 2, n);
    segtree[n][node] = segtree[n][2 * node + 1] + segtree[n][2 * node + 2];
}

int calc(int a, int b) {
    long long sum = 0;
    while (1) {
        int j = pos[a].first;
        if (j == pos[b].first) {
            sum += getSum(0, paths[j].size() - 1, pos[a].second, pos[b].second - 1, 0, j);
            break;
        }
        sum += getSum(0, paths[j].size() - 1, pos[a].second, paths[j].size() - 1, 0, j);
        a = parent[tail[a]];
    }
    return sum;
}

void upd(int a, int b) {
     while (1) {
        int j = pos[a].first;
        if (j == pos[b].first) {
            incUpdate(0, 0, paths[j].size() - 1, pos[a].second, pos[b].second - 1, 1, j);
            break;
        }
        incUpdate(0, 0, paths[j].size() - 1, pos[a].second, paths[j].size() - 1, 1, j);
        a = parent[tail[a]];
    }

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
        lazy[i].resize(4 * paths[i].size());
        segtree[i].resize(4 * paths[i].size());
        build(0, paths[i].size() - 1, 0, i);
    }
    for (int i = 0; i < q; i++) {
        char c;
        cin >> c;

        int u, v;
        cin >> u >> v;
        if (c == 'Q') {
            u--, v--;
            if (tin[u] > tin[v]) {
                swap(u, v);
            }
            int l = lca(u, v);
            int ans = calc(v, l);
            if (u != l) {
                ans = max(ans, calc(u, l));
            }
            cout << ans << endl;

        } else {
            u--, v--;
            if (tin[u] > tin[v]) {
                swap(u, v);
            }
            int l = lca(u, v);
            upd(v, l);
            if (u != l) {
                upd(u, l);
            }
        }
    }
    return 0;
}
