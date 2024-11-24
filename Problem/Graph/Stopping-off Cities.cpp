//https://www.spoj.com/problems/STOPCITY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 5e5 + 5;

vector<int> adj[N];

int depth[N];
int low[N];
int id[N];
int ans_comp[N];
int ans[N];
int parent[N];
bool vis[N];
bool is_art[N];
vector<vector<int>> bicomp;
vector<int> cur;

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
            low[u] = min(low[u], depth[v]);
        } else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= depth[u]) {
                is_art[u] = (depth[u] > 0 || depth[v] > 2);
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
            }
        }
    }
    return;
}

void dfs_path(int u, int p) {
    parent[u] = p;
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs_path(v, u);
        }
    }
    return;
}

int main() {
	IOS;
	int n;
	cin >> n;
	int u, v;
	cin >> u >> v;
	while (u != -1) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        cin >> u >> v;
	}
	int st, en;
	cin >> st >> en;
	adj[st].push_back(en);
	adj[en].push_back(st);
	for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, i);
            if (adj[i].size() == 0) {
                vector<int> a{i};
                bicomp.push_back(a);
            }
        }
	}
	for (int i = 0; i < n; i++) {
        vis[i] = false;
	}
	for (int i = 0; i < bicomp.size(); i++) {
        for (int u : bicomp[i]) {
            if (!is_art[u]) {
                id[u] = i;
            }
        }
	}
	dfs_path(st, st);
    u = en;
	while (u != st) {
        if (!is_art[u]) {
            ans_comp[id[u]] = true;
        }
        u = parent[u];
	}
	if (!is_art[u]) {
        ans_comp[id[u]] = true;
    }
    for (int i = 0; i < bicomp.size(); i++) {
        if (ans_comp[i]) {
            for (int u : bicomp[i]) {
                ans[u] = true;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (ans[i]) {
            cout << i << " ";
        }
    }
	return 0;
}
