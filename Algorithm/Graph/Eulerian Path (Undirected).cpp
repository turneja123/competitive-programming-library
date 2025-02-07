//https://cses.fi/problemset/task/1691
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

vector<pair<int, int>> adj[N];
vector<int> ans;

int deg[N];
bool vis[N];

void dfs(int u) {
    while (adj[u].size()) {
        auto [v, e] = adj[u].back();
        adj[u].pop_back();
        if (vis[e]) {
            continue;
        }
        vis[e] = true;
        dfs(v);
    }
    ans.push_back(u);
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
        adj[u].push_back(make_pair(v, i));
        adj[v].push_back(make_pair(u, i));
        deg[u]++;
        deg[v]++;
	}
	bool can = true;
	for (int i = 0; i < n; i++) {
        if (deg[i] % 2 == 1) {
            can = false;
        }
	}
	if (!can) {
        cout << "IMPOSSIBLE";
        return 0;
	}
	dfs(0);
	reverse(ans.begin(), ans.end());
	if (ans.size() != m + 1) {
        cout << "IMPOSSIBLE";
	} else {
        for (int u : ans) {
            cout << u + 1 << " ";
        }
	}
	return 0;
}
