//https://www.spoj.com/problems/CAC/
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
bool vis[N];
int parent[N];

vector<vector<int>> cycles;

void dfs(int u, int p) {
    vis[u] = true;
    parent[u] = p;
    for (int v : adj[u]) {
        if (!vis[v]) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        } else if (depth[u] - depth[v] > 1) {
            vector<int> cyc;
            int x = u;
            while (x != v) {
                cyc.push_back(x);
                x = parent[x];
            }
            cyc.push_back(v);
            cycles.push_back(cyc);
        }
    }
    return;
}

int main() {
	IOS;
	int t;
	cin >> t;
	for (int tt = 1; tt <= t; tt++) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, 0);
        unsigned long long ans = 1;
        for (int i = 0; i < cycles.size(); i++) {
            ans *= cycles[i].size();
        }
        cout << "Case " << tt << ": " << ans << endl;
        cycles.clear();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            vis[i] = false, depth[i] = 0, parent[i] = 0;
        }
	}

	return 0;
}
