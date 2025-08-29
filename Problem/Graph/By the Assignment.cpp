//https://codeforces.com/contest/2135/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const ll M = 998244353;

vector<int> adj[N];

int a[N];
int depth[N];
int low[N];
bool vis[N];
bool is_art[N];
vector<vector<int>> bicomp;
vector<vector<pair<int, int>>> bicomp_edges;
vector<int> cur;
vector<pair<int, int>> cure;

int timer = 0;

void dfs(int u, int p) {
    vis[u] = true;
    depth[u] = low[u] = timer++;
    cur.push_back(u);
    for (int v : adj[u]) {
        if (v == p) {
            continue;
        }
        if (vis[v]) {
            if (depth[v] < depth[u]) {
                cure.push_back({u, v});
            }
            low[u] = min(low[u], depth[v]);
        } else {
            cure.push_back({u, v});
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
                bicomp.push_back(bcc);

                vector<pair<int, int>> bcc_edges;
                while (cure.size()) {
                    auto e = cure.back();
                    cure.pop_back();
                    bcc_edges.push_back(e);
                    if ((e.first == u && e.second == v) || (e.first == v && e.second == u)) {
                        break;
                    }
                }
                bicomp_edges.push_back(bcc_edges);
            }
        }
    }
    return;
}

int parent[N];
int sz[N];
int odd[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    a = dsu_find(a), b = dsu_find(b);
    if (a == b) {
        return;
    }
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    odd[a] |= odd[b];
    parent[b] = a;
}

vector<int> adj_check[N];
set<int> st[N];
int color[N];
bool can = true;

void dfs_check(int u) {
    for (int v : adj_check[u]) {
        if (color[v] == -1) {
            color[v] = color[u] ^ 1;
            dfs_check(v);
        } else if (color[v] == color[u]) {
            can = false;
        }
    }
    return;
}


int main() {
	IOS;

	int t;
	cin >> t;
	while (t--) {
        int n, m, v;
        cin >> n >> m >> v;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            parent[i] = i;
            sz[i] = 1;
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, i);
            }
        }


        for (int i = 0; i < bicomp.size(); i++) {
            if (bicomp[i].size() < 3) {
                continue;
            }
            for (auto [u, v] : bicomp_edges[i]) {
                adj_check[u].push_back(v);
                adj_check[v].push_back(u);
            }
            for (int u : bicomp[i]) {
                color[u] = -1;
            }
            can = true;
            for (int u : bicomp[i]) {
                if (color[u] == -1) {
                    color[u] = 0;
                    dfs_check(u);
                }
            }
            for (int u : bicomp[i]) {
                odd[u] = !can;
                adj_check[u].clear();
            }
            int u = bicomp[i][0];
            for (int v : bicomp[i]) {
                dsu_unite(u, v);
            }
        }

        ll ans = 1;
        for (int i = 0; i < n; i++) {
            int u = dsu_find(i);
            if (a[i] != -1) {
                st[u].insert(a[i]);
            }
        }
        for (int i = 0; i < n; i++) {
            if (dsu_find(i) == i) {
                if (st[i].size() == 0) {
                    if (!odd[i]) {
                        ans = ans * v % M;
                    }
                } else if (st[i].size() == 1) {
                    if (odd[i] && *st[i].begin() != 0) {
                        ans = 0;
                    }
                } else {
                    ans = 0;
                }
            }
        }
        cout << ans << endl;

        cur.clear();
        cure.clear();
        bicomp.clear();
        bicomp_edges.clear();
        for (int i = 0; i < n; i++) {
            vis[i] = false;
            low[i] = 0;
            depth[i] = 0;
            is_art[i] = 0;
            adj[i].clear();
            st[i].clear();
            odd[i] = 0;
        }
        timer = 0;

	}
	return 0;
}
