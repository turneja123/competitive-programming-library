//https://arena.petlja.org/sr-Latn-RS/competition/2024-2025-kv2-testiranje#tab_140267
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 3e6 + 5;

vector<int> adj[N];
vector<int> blockcut[N];

pair<int, int> compr[N];
int val[N];
int a[N];
int depth[N];
int low[N];
bool is_art[N];
int compid[N];
int id[N];
int rev_id[N];
bool vis[N];
vector<vector<int>> bicomp;
vector<int> cur;
vector<int> t[N];

int timer = 0;
vector<int> tin, tout;
vector<vector<int>> up;
int lg;

const int MAX = 6e7 + 5;

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;
int root[N];

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
        nodes[node].val = nodes[node_prev].val + val;
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
    nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
    return;
}

int query(int node_l, int node_u, int node_v, int l, int r, int lq, int rq) {
    if (lq > r || rq < l) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node_u].val + nodes[node_v].val - 2 * nodes[node_l].val;
    }
    int mid = (l + r) / 2;
    return query(nodes[node_l].left, nodes[node_u].left, nodes[node_v].left, l, mid, lq, rq) + query(nodes[node_l].right, nodes[node_u].right, nodes[node_v].right, mid + 1, r, lq, rq);
}

int traverse(int node_p, int node_l, int node_u, int node_v, int med, int lf, int rt, int l, int u, int v, int m) {
    if (lf == rt) {
        return lf;
    }
    int mid = (lf + rt) / 2;
    int k = nodes[nodes[node_u].left].val + nodes[nodes[node_v].left].val - nodes[nodes[node_l].left].val - (node_p == -1 ? 0 : nodes[nodes[node_p].left].val);
    if ((u == l || v == l) && l < m) {
        k += a[rev_id[l]] <= mid && a[rev_id[l]] >= lf;
    }
    if (u != l && u < m && a[rev_id[u]] <= mid && a[rev_id[u]] >= lf ) {
        k++;
    }
    if (v != l && v < m && a[rev_id[v]] <= mid && a[rev_id[v]] >= lf) {
        k++;
    }
    if (med - k > 0) {
        return traverse((node_p == -1 ? -1 : nodes[node_p].right), nodes[node_l].right, nodes[node_u].right, nodes[node_v].right, med - k, mid + 1, rt, l, u, v, m);
    } else {
        return traverse((node_p == -1 ? -1 : nodes[node_p].left), nodes[node_l].left, nodes[node_u].left, nodes[node_v].left, med, lf, mid, l, u, v, m);
    }

}

void dfs(int u, int p) {
    vis[u] = true;
    depth[u] = low[u] = timer++;
    cur.push_back(u);
    for (int v : adj[u]) {
        if (v == p) {
            continue;
        }
        if (vis[v]) {
            low[u] = min(low[u], depth[v]);
        } else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= depth[u]) {
                is_art[u] = (depth[u] > 0 || depth[v] > 1);
                vector<int> bcc;
                while (cur.size()) {
                    int w = cur.back();
                    cur.pop_back();
                    bcc.push_back(w);
                    if (w == v) {
                        break;
                    }
                }
                bcc.push_back(u);
                for (int x : bcc) {
                    compid[x] = bicomp.size();
                }
                bicomp.push_back(bcc);
            }
        }
    }
    return;
}

void dfs_tree(int v, int p, int cur_root, int k, int m) {
    if (v < m) {
        root[v] = cur_root;
        int x = rev_id[v];
        int cur = idx;
        nodes[idx++] = Node();
        update(root[v], cur, 0, k - 1, a[x], -1);
        root[v] = cur;
    } else {
        root[v] = cur_root;
        for (int x : bicomp[v - m]) {
            t[v].push_back(a[x]);
            int cur = idx;
            nodes[idx++] = Node();
            update(root[v], cur, 0, k - 1, a[x], 1);
            root[v] = cur;
        }
    }

    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : blockcut[v]) {
        if (u != p) {
            dfs_tree(u, v, root[v], k, m);
        }
    }
    tout[v] = timer++;
}

bool is_ancestor(int u, int v, int f) {
    if (f) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }
    return tin[u] < tin[v] && tout[u] > tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v, 1)) {
        return u;
    }
    if (is_ancestor(v, u, 1)) {
        return v;
    }
    for (int i = lg; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v, 1)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

int get(int a, int m) {
    if (is_art[a]) {
        a = id[a];
    } else {
        a = compid[a] + m;
    }
    return a;
}

int main() {
    IOS;
    int n, m, q, p;
	cin >> n >> m >> q >> p;
	int nn = n;
	for (int i = 0; i < n; i++) {
        cin >> a[i];
        compr[i] = make_pair(a[i], i);
    }
    sort(compr, compr + n);
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && compr[i].first > compr[i - 1].first) {
            k++;
        }
        val[k] = compr[i].first;
        a[compr[i].second] = k;
    }
    k++;
	for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u > v) {
            swap(u, v);
        }
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
	}
	dfs(0, 0);
	m = 0;
	for (int i = 0; i < n; i++) {
        if (is_art[i]) {
            rev_id[m] = i;
            id[i] = m++;
        }
	}
	for (int i = 0; i < bicomp.size(); i++) {
        for (int u : bicomp[i]) {
            if (is_art[u]) {
                blockcut[id[u]].push_back(m + i);
                blockcut[m + i].push_back(id[u]);
            }
        }
	}
	n = m + bicomp.size();
    lg = ceil(log2(n));
    up.assign(n, vector<int>(lg + 1));
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    nodes[idx++] = Node();
    build(0, 0, k - 1);
    dfs_tree(0, 0, 0, k, m);
    for (int i = m; i < n; i++) {
        sort(t[i].begin(), t[i].end());
    }
    int ans = 0;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u = (u + ans * p - 1) % nn, v = (v + ans * p - 1) % nn;
        if (u == v) {
            ans = val[a[u]];
            cout << ans << endl;
            continue;
        }
        u = get(u, m), v = get(v, m);
        if (u == v) {
            int med = ((int)t[u].size() + 1) / 2;
            ans = t[u][med - 1];
            ans = val[ans];
            cout << ans << endl;
            continue;
        }
        int l = lca(u, v);
        int ct = query(root[l], root[u], root[v], 0, k - 1, 0, k - 1);
        if (l < m) {
            ct--;
        } else {
            ct += t[l].size();
        }
        if ((u == l || v == l) && l < m) {
            ct++;
        }
        if (u != l && u < m) {
            ct++;
        }
        if (v != l && v < m) {
            ct++;
        }
        int med = (ct + 1) / 2;
        int p = (l == 0 ? -1 : up[l][0]);
        ans = val[traverse((p == -1 ? -1 : root[p]), root[l], root[u], root[v], med, 0, k - 1, l, u, v, m)];
        cout << ans << endl;
    }



    return 0;
}
