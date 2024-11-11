//https://cses.fi/problemset/task/1756/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

set<int> adj[N];
set<pair<int, int>> st;

int depth[N];
bool vis[N];
vector<pair<int, int>> edges;

void dfs(int u, int p) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            st.insert(make_pair(u, v));
        } else if (depth[u] - depth[v] > 1) {
            st.insert(make_pair(v, u));
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
        u--, v--;
        adj[u].insert(v);
        adj[v].insert(u);
        edges.emplace_back(u, v);
	}
	for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, i);
        }
	}
    for (int i = 0; i < m; i++) {
        int u = edges[i].first, v = edges[i].second;
        auto it = st.find(make_pair(u, v));
        if (it == st.end()) {
            swap(u, v);
        }
        cout << u + 1 << " " << v + 1 << endl;
    }

	return 0;
}
