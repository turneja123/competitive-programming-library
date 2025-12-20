//https://qoj.ac/contest/2668/problem/15449
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

vector<pair<int, ll>> adj[N];

ll a[N];
ll subtree[N];
int depth[N];
int low[N];
bool vis[N];
int timer = 0;

string ans =  "TAK";

void dfs(int u, int p) {
    vis[u] = true;
    depth[u] = low[u] = timer++;
    subtree[u] = a[u];
    for (auto [v, wt] : adj[u]) {
        if (v == p) {
            continue;
        }
        if (vis[v]) {
            low[u] = min(low[u], depth[v]);
        } else {
            dfs(v, u);
            subtree[u] += subtree[v];
            low[u] = min(low[u], low[v]);
            if (low[v] > depth[u] && abs(subtree[v]) > wt) {
                ans = "NIE";
            }
        }
    }
    return;
}

int main() {
	IOS;
	int t;
	cin >> t;
	while (t--) {
        int n, m;
        cin >> n >> m;
        timer = 0; ans = "TAK";
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < m; i++) {
            int u, v; ll wt;
            cin >> u >> v >> wt;
            u--, v--;
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }
        dfs(0, 0);
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            vis[i] = 0;
            adj[i].clear();
        }

	}
	return 0;
}
