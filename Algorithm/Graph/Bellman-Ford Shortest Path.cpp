//https://cses.fi/problemset/task/1673/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 5005;
const long long INF = 1e18;

long long dist[N];
vector<tuple<int, int, int>> edges;
vector<int> rev[N];
bool vis[N];

void dfs(int u) {
    vis[u] = true;
    for (int v : rev[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
    return;
}

int main() {
	IOS;
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        rev[v].push_back(u);
        edges.push_back(make_tuple(u, v, -wt));
	}
	dfs(n - 1);
	for (int i = 0; i < n; i++) {
        dist[i] = INF;
	}
	bool cyc = false;
	dist[0] = 0;
	for (int j = 1; j <= n; j++) {
        for (int i = 0; i < m; i++) {
            auto [u, v, wt] = edges[i];
            if (!vis[u] || !vis[v] || dist[u] == INF) {
                continue;
            }
            if (dist[v] > dist[u] + wt) {
                dist[v] = dist[u] + wt;
                if (j == n) {
                    cyc = true;
                }
            }
        }
	}
	if (cyc) {
        cout << -1;
	} else {
        cout << -dist[n - 1];
	}
	return 0;
}
