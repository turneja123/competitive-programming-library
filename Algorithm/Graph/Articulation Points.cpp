//https://cses.fi/problemset/task/2077
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
vector<int> ans;

void dfs(int u, int p) {
    vis[u] = true;
    low[u] = N;
    int child = 0; bool art = false;
    for (int v : adj[u]) {
        if (!vis[v]) {
            child++;
            depth[v] = depth[u] + 1;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= depth[u]) {
                art = true;
            }
        } else if (depth[u] - depth[v] > 1) {
            low[u] = min(low[u], depth[v]);
        }
    }
    if (art && !(u == p && child < 2)) {
        ans.push_back(u);
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
	for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, i);
        }
	}
	cout << ans.size() << endl;
    for (int u : ans) {
        cout << u + 1 << " ";
    }

	return 0;
}
