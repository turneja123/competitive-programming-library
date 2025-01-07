//https://www.spoj.com/problems/GSS7/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e12;

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

struct Node {
    long long pref;
    long long suf;
    long long sum;
    long long val;
    int setVal;
    bool setValid;
    Node() : pref(0), suf(0), sum(0), val(0), setVal(0), setValid(false) {}
    Node(long long x) : pref(x), suf(x), sum(x), val(x), setVal(0), setValid(false) {}
};

vector<Node> segtree[N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.val == -INF) {
        return right;
    }
    if (right.val == -INF) {
        return left;
    }
    node.sum = left.sum + right.sum;
    node.pref = max(left.pref, left.sum + right.pref);
    node.suf = max(right.suf, right.sum + left.suf);
    node.val = max({left.val, right.val, node.pref, node.suf, left.suf + right.pref});
    return node;
}

void compose(int parent, int child, int n) {
    if (segtree[n][parent].setValid) {
        segtree[n][child].setValid = true;
        segtree[n][child].setVal = segtree[n][parent].setVal;
    }
}

void apply(int node, int l, int r, int n) {
    if (segtree[n][node].setValid) {
        segtree[n][node].sum = (r - l + 1) * segtree[n][node].setVal;
        if (segtree[n][node].setVal > 0) {
            segtree[n][node].pref = (r - l + 1) * segtree[n][node].setVal;
            segtree[n][node].suf = (r - l + 1) * segtree[n][node].setVal;
            segtree[n][node].val = (r - l + 1) * segtree[n][node].setVal;
        } else {
            segtree[n][node].pref = segtree[n][node].setVal;
            segtree[n][node].suf = segtree[n][node].setVal;
            segtree[n][node].val = segtree[n][node].setVal;
        }
    }
    if (l != r) {
        compose(node, 2 * node + 1, n);
        compose(node, 2 * node + 2, n);
    }
    segtree[n][node].setValid = false;
}

Node query(int l, int r, int lq, int rq, int node, int n) {
    if (l > rq || r < lq) {
        Node sentinel(-INF);
        return sentinel;
    }
    apply(node, l, r, n);
    if (lq <= l && rq >= r) {
        return segtree[n][node];
    }

    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1, n), query(mid + 1, r, lq, rq, 2 * node + 2, n));
}

void setUpdate(int node, int l, int r, int lq, int rq, int val, int n) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[n][node].setValid = true;
        segtree[n][node].setVal = val;
        return;
    }
    apply(node, l, r, n);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val, n);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val, n);
    apply(2 * node + 1, l, mid, n);
    apply(2 * node + 2, mid + 1, r, n);
    segtree[n][node] = combine(segtree[n][2 * node + 1], segtree[n][2 * node + 2]);
}


void build(int l, int r, int node, int n) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[n][node] = Node(vals[paths[n][l]]);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, n);
    build(mid + 1, r, 2 * node + 2, n);
    segtree[n][node] = combine(segtree[n][2 * node + 1], segtree[n][2 * node + 2]);
}

Node calc(int a, int b, int flag) {
    vector<Node> nodes;
    while (1) {
        int j = pos[a].first;
        if (j == pos[b].first) {
            nodes.push_back(query(0, paths[j].size() - 1, pos[a].second, pos[b].second - flag, 0, j));
            break;
        }
        nodes.push_back(query(0, paths[j].size() - 1, pos[a].second, paths[j].size() - 1, 0, j));
        a = parent[tail[a]];
    }
    Node node = nodes[0];
    for (int i = 1; i < nodes.size(); i++) {
        node = combine(node, nodes[i]);
    }
    return node;
}

void upd(int a, int b, int x, int flag) {
    while (1) {
        int j = pos[a].first;
        if (j == pos[b].first) {
            setUpdate(0, 0, paths[j].size() - 1, pos[a].second, pos[b].second - flag, x, j);
            break;
        }
        setUpdate(0, 0, paths[j].size() - 1, pos[a].second, paths[j].size() - 1, x, j);
        a = parent[tail[a]];
    }
    return;
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
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            if (tin[u] > tin[v]) {
                swap(u, v);
            }
            int l = lca(u, v);
            Node left = calc(v, l, 0);
            long long ans = left.val;
            if (u != l) {
                Node right = calc(u, l, 1);
                ans = max({ans, right.val, left.suf + right.suf});
            }
            cout << max(0ll, ans) << endl;

        } else {
            int u, v, x;
            cin >> u >> v >> x;
            u--, v--;
            if (tin[u] > tin[v]) {
                swap(u, v);
            }
            int l = lca(u, v);
            upd(v, l, x, 0);
            if (u != l) {
                upd(u, l, x, 1);
            }
        }
    }
    return 0;
}
