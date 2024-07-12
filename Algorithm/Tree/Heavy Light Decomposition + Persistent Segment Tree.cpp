//https://www.codechef.com/problems/PSHTTR
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 2e7 + 5;

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
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        int u = it->first, wt = it->second;
        if (u != p) {
            vals[u] =  wt;
            parent[u] = v;
            ct += dfs(u, v, 1);
        }
    }
    tout[v] = ++timer;
    return sz[v] = ct;
}

void dfs_markedges(int v, int p) {
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        int u = it->first, wt = it->second;
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

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

vector<int> root[N];
vector<int> val[N];
int m[N];

void build(int node, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    nodes[node].left = idx;
    nodes[idx++] = Node();
    nodes[node].right = idx;
    nodes[idx++] = Node();
    build(nodes[node].left, l, mid);
    build(nodes[node].right, mid + 1, r);
    return;
}

void update(int node_prev, int node, int l, int r, int ind, int val) {
    if (l == r) {
        nodes[node].val = nodes[node_prev].val ^ val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[node].right = nodes[node_prev].right;
        update(nodes[node_prev].left, nodes[node].left, l, mid, ind, val);
    } else {
        nodes[node].right = idx;
        nodes[idx++] = Node();
        nodes[node].left = nodes[node_prev].left;
        update(nodes[node_prev].right, nodes[node].right, mid + 1, r, ind, val);
    }
    nodes[node].val = nodes[nodes[node].left].val ^ nodes[nodes[node].right].val;
    return;
}

int query(int node_l, int node_r, int l, int r, int lq, int rq) {
    if (lq > r || rq < l) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node_r].val ^ nodes[node_l].val;
    }
    int mid = (l + r) / 2;
    return query(nodes[node_l].left, nodes[node_r].left, l, mid, lq, rq) ^ query(nodes[node_l].right, nodes[node_r].right, mid + 1, r, lq, rq);
}

int calc(int a, int b, int flag, int k) {
    int ans = 0;
    while (1) {
        int j = pos[a].first;
        int r = upper_bound(val[j].begin(), val[j].end(), k) - val[j].begin();
        r--;
        if (j == pos[b].first) {
            if (r >= 0) {
                ans ^= query(root[j][pos[a].second], root[j][pos[b].second - flag + 1], 0, m[j] - 1, 0, r);
            }
            break;
        }
        if (r >= 0) {
            ans ^= query(root[j][pos[a].second], root[j][paths[j].size()], 0, m[j] - 1, 0, r);
        }
        a = parent[tail[a]];
    }
    return ans;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
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
                int j = paths.size();
                vector<int> path;
                vector<int> compr_vals;

                vector<pair<int, int>> compr;
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
                    pos[path[i]] = {j, i};
                    compr.push_back(make_pair(vals[path[i]], i));

                }
                compr_vals.resize(path.size());
                sort(compr.begin(), compr.end());
                m[j] = 0;
                for (int i = 0; i < path.size(); i++) {
                    if (i > 0 && compr[i].first > compr[i - 1].first) {
                        m[j]++;
                    }
                    if (m[j] == val[j].size()) {
                        val[j].push_back(compr[i].first);
                    }
                    compr_vals[compr[i].second] = m[j];

                }
                root[j].resize(path.size() + 1);
                m[j]++;
                root[j][0] = idx;
                nodes[idx++] = Node();
                build(root[j][0], 0, m[j] - 1);
                for (int i = 0; i < path.size(); i++) {
                    root[j][i + 1] = idx;
                    nodes[idx++] = Node();
                    update(root[j][i], root[j][i + 1], 0, m[j] - 1, compr_vals[i], val[j][compr_vals[i]]);
                }

                paths.push_back(path);
            }
        }
        cin >> q;
        for (int i = 0; i < q; i++) {
            int u, v, k;
            cin >> u >> v >> k;
            u--, v--;
            if (tin[u] > tin[v]) {
                swap(u, v);
            }
            int l = lca(u, v);
            int ans = calc(v, l, 1, k);
            if (u != l) {
                ans ^= calc(u, l, 1, k);
            }
            cout << ans << endl;
        }
        for (int i = 0; i < n; i++) {
            m[i] = 0;
            adj[i].clear();
            root[i].clear();
            val[i].clear();
        }
        tin.clear();
        tout.clear();
        up.clear();
        paths.clear();
        idx = 0, timer = 0;
    }

    return 0;
}
