//https://judge.yosupo.jp/problem/biconnected_components
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
            }
        }
    }
    return;
}

int main() {
	IOS;
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, i);
            if (adj[i].size() == 0) {
                vector<int> a{i};
                bicomp.push_back(a);
            }
        }
	}
	int s = bicomp.size();
	cout << s << endl;
	for (int i = 0; i < s; i++) {
        cout << bicomp[i].size() << " ";
        for (int u : bicomp[i]) {
            cout << u << " ";
        }
        cout << endl;
	}
	return 0;
}
