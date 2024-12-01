//https://cses.fi/problemset/task/1705/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 5e5 + 5;

vector<int> adj[N];
vector<int> blockcut[N];

int depth[N];
int low[N];
bool vis[N];
bool is_art[N];
int compid[N];
int id[N];
vector<vector<int>> bicomp;
vector<int> cur;

int timer = 0;
vector<int> tin, tout;
vector<vector<int>> up;
int lg;

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

void dfs_tree(int v, int p) {
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : blockcut[v]) {
        if (u != p) {
            dfs_tree(u, v);
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
	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
	}
    dfs(0, 0);
    if (adj[0].size() == 0) {
        vector<int> a{0};
        compid[0] = bicomp.size();
        bicomp.push_back(a);
    }
	m = 0;
	for (int i = 0; i < n; i++) {
        if (is_art[i]) {
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
    dfs_tree(0, 0);
    for (int i = 0; i < q; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--, c--;
        if (c == a || c == b) {
            cout << "NO" << endl;
            continue;
        }
        if (!is_art[c] || a == b) {
            cout << "YES" << endl;
            continue;
        }
        a = get(a, m), b = get(b, m), c = get(c, m);
        int l = lca(a, b);
        if ((is_ancestor(c, a, 1) && !is_ancestor(c, l, 0)) || (is_ancestor(c, b, 1) && !is_ancestor(c, l, 0))) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
	return 0;
}
