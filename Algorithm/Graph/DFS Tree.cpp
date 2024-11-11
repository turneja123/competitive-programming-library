//https://cses.fi/problemset/task/2177
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

vector<int> adj[N];

int depth[N];
int low[N];
bool vis[N];
bool bridge = false;
vector<pair<int, int>> ans;

void dfs(int u, int p) {
    vis[u] = true;
    low[u] = N;
    for (int v : adj[u]) {
        if (!vis[v]) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            ans.emplace_back(u, v);
        } else if (depth[u] - depth[v] > 1) {
            low[u] = min(low[u], depth[v]);
            ans.emplace_back(u, v);
        }
    }
    if (depth[u] > 0 && low[u] >= depth[u]) {
        bridge = true;
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
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
	}
	bool connected = true;
	dfs(0, 0);
	for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            connected = false;
        }
	}
	if (bridge || !connected) {
        cout << "IMPOSSIBLE";
        return 0;
	}
    for (pair<int, int> p : ans) {
        cout << p.first + 1 << " " << p.second + 1 << endl;
    }

	return 0;
}
