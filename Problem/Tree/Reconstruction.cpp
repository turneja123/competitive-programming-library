//https://dmoj.ca/problem/lkp18c2p6
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
int timer = 0, euler = 0, lg;
vector<pair<int, int>> adj[N];
int vals[N];
int parent[N];
int sz[N];
int tail[N];
pair<int, int> pos[N];
bool head[N];
int edges[N];
int depth[N];
int tour[N];

pair<int, int> edge_upd[N];

int e[N];
int original[N];
int mark[N];

int root = -1;
long long sum = 0;

set<int> subgraph;

int dfs(int v, int p, int ct) {
    tour[v] = euler++;
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        int u = it->first, wt = it->second;
        if (u != p) {
            vals[u] = wt;
            parent[u] = v;
            depth[u] = depth[v] + 1;
            ct += dfs(u, v, 1);
        }
    }
    tout[v] = ++timer;
    return sz[v] = ct;
}

void dfs_markedges(int v, int p) {
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        int u = it->first;
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
int segtree_sub[4 * N];

int rsq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree_sub[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return rsq(l, mid, lq, rq, 2 * node + 1) + rsq(mid + 1, r, lq, rq, 2 * node + 2);
}

void update_sub(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree_sub[node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update_sub(l, mid, ind, val, 2 * node + 1);
    } else {
        update_sub(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree_sub[node] = segtree_sub[2 * node + 1] + segtree_sub[2 * node + 2];
}

long long query(int l, int r, int lq, int rq, int node, int n) {
    if (l > rq || r < lq || lq > rq) {
        return 0;
    }

    if (lq <= l && rq >= r) {
        return segtree[n][node];
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1, n) + query(mid + 1, r, lq, rq, 2 * node + 2, n);
}

void update(int l, int r, int ind, long long val, int node, int n) {
    if (l == r) {
        segtree[n][node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1, n);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2, n);
    }
    segtree[n][node] = segtree[n][2 * node + 1] + segtree[n][2 * node + 2];
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

long long calc(int a, int b, int flag) {
    long long ans = 0;
    while (1) {
        int j = pos[a].first;
        if (j == pos[b].first) {
            ans += query(0, paths[j].size() - 1, pos[a].second, pos[b].second - flag, 0, j);
            break;
        }
        ans += query(0, paths[j].size() - 1, pos[a].second, paths[j].size() - 1, 0, j);
        a = parent[tail[a]];
    }
    return ans;
}

int kth(int v, int k) {
    int i = 0;
    while (k > 0) {
        int j = 1 << i, c = k & j;
        if (c != 0) {
            v = up[v][i];
            k ^= j;
        }
        i++;
    }
    return v;
}

void add_node(int u, int n) {
    subgraph.insert(u);
    assert(mark[u] == 0);
    if (root == -1) {
        root = u;
        update_sub(0, n - 1, tour[u], 1, 0);
        mark[u] = 1;
        return;
    }
    int l = lca(u, root);
    if (l != root) {
        sum += calc(u, l, 1);
        sum += calc(root, l, 1);
        update_sub(0, n - 1, tour[u], 1, 0);
        root = l;
    } else {
        int ct = rsq(0, n - 1, tour[u], tour[u] + sz[u] - 1, 0);
        if (ct == 0) {
            int l = 0, r = depth[u] - depth[root], leaf = u;
            while (l <= r) {
                int mid = (l + r) / 2;
                int ancestor = kth(u, mid), cur = rsq(0, n - 1, tour[ancestor], tour[ancestor] + sz[ancestor] - 1, 0);
                if (cur == 0) {
                    leaf = ancestor;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            sum += calc(u, leaf, ((leaf == root) ? 1 : 0));
            update_sub(0, n - 1, tour[u], 1, 0);
        } else {
            update_sub(0, n - 1, tour[u], 1, 0);
        }
    }
    mark[u] = 1;
    return;
}

void delete_node(int u, int n) {
    subgraph.erase(u);
    update_sub(0, n - 1, tour[u], 0, 0);
    if (subgraph.size() < 2) {
        sum = 0;
        mark[u] = 0;
        return;
    }
    int r = depth[u] - depth[root], ancestor = kth(u, r - 1);
    if (u == root || rsq(0, n - 1, tour[ancestor], tour[ancestor] + sz[ancestor] - 1, 0) == 0) {
        sum -= calc(u, root, 1);
        int test = *subgraph.begin();
        if (test != root) {
            int l = 0, r = depth[test] - depth[root], new_root = root;
            while (l <= r) {
                int mid = (l + r) / 2;
                int ancestor = kth(test, mid), cur = rsq(0, n - 1, tour[ancestor], tour[ancestor] + sz[ancestor] - 1, 0);
                if (cur == subgraph.size()) {
                    new_root = ancestor;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (new_root != root) {
                sum -= calc(new_root, root, 1);
                root = new_root;
            }
        }
        mark[u] = 0;
        return;
    }
    int ct = rsq(0, n - 1, tour[u], tour[u] + sz[u] - 1, 0);
    if (ct == 0) {
        int l = 0, r = depth[u] - depth[root], leaf = u;
        while (l <= r) {
            int mid = (l + r) / 2;
            int ancestor = kth(u, mid), cur = rsq(0, n - 1, tour[ancestor], tour[ancestor] + sz[ancestor] - 1, 0);
            if (cur == 0) {
                leaf = ancestor;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        sum -= calc(u, leaf, 0);
    }
    mark[u] = 0;
    return;
}

int main() {
    IOS;
    int n, q, k;
    cin >> n >> q >> k;
    lg = ceil(log2(n));
    up.assign(n, vector<int>(lg + 1));
    tin.resize(n);
    tout.resize(n);
    for (int i = 0; i < k; i++) {
        cin >> original[i];
        original[i]--;
    }
    for (int i = 0; i < n; i++) {
        head[i] = true;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        edge_upd[i] = make_pair(u, v);
        e[i] = wt;
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
    for (int i = 0; i < k; i++) {
        add_node(original[i], n);
    }
    cout << sum << endl;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 2) {
            int ind, wt;
            cin >> ind >> wt;
            ind--;
            int u = edge_upd[ind].first, v = edge_upd[ind].second;
            if (v == parent[u]) {
                swap(u, v);
            }
            if (is_ancestor(root, u) && rsq(0, n - 1, tour[v], tour[v] + sz[v] - 1, 0) > 0) {
                sum += wt - e[ind];
            }
            e[ind] = wt;
            int j = pos[v].first;
            update(0, paths[j].size() - 1, pos[v].second, wt, 0, j);
            cout << sum << endl;

        } else {
            int u;
            cin >> u;
            u--;
            if (!mark[u]) {
                add_node(u, n);
            } else {
                delete_node(u, n);
            }
            cout << sum << endl;

        }
    }

    return 0;
}
