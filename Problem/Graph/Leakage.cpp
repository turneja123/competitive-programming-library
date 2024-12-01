//https://codeforces.com/gym/102512/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e6 + 5;

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
vector<vector<int>> sum;
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

void dfs_tree(int v, int p, int m) {
    tin[v] = timer++;
    up[v][0] = p;
    sum[v][0] = v < m;
    for (int i = 1; i <= lg; i++) {
        sum[v][i] = sum[v][i - 1] + sum[up[v][i - 1]][i - 1];
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : blockcut[v]) {
        if (u != p) {
            depth[u] = depth[v] + 1;
            dfs_tree(u, v, m);
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

int calc(int u, int k) {
    int ans = 0;
    for (int i = lg; i >= 0; i--) {
        int c = k & (1 << i);
        if (c) {
            ans += sum[u][i];
            u = up[u][i];
        }
    }
    return ans;
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
	cin >> n >> m;
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
    sum.assign(n, vector<int>(lg + 1));
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    depth[0] = 0;
    dfs_tree(0, 0, m);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        a = get(a, m), b = get(b, m);
        int l = lca(a, b);
        int ans = 0;
        if (a != l) {
            ans += calc(a, depth[a] - depth[l]);
        }
        if (b != l) {
            ans += calc(b, depth[b] - depth[l]);
        }
        if (a != l && b != l && l < m) {
            ans++;
        }
        if (a != l && a < m) {
            ans--;
        }
        if (b != l && b < m) {
            ans--;
        }
        cout << ans << endl;
    }
	return 0;
}
