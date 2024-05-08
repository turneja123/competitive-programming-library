//https://cses.fi/problemset/task/2138/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e4 + 5;

bitset<N> b[N];
vector<int> adj[N];
bool vis[N];

void dfs(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs(v);
        }
        b[u] |= b[v];
    }
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
	}
	for (int i = 0; i < n; i++) {
        b[i].set(i);
	}
	for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
	}
	for (int i = 0; i < n; i++) {
        cout << b[i].count() << " ";
	}

	return 0;
}
