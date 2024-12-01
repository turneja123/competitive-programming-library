//https://cses.fi/problemset/task/1668/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

bool can = true;
vector<int> adj[N];
int ans[N];

void dfs(int u) {
    for (int v : adj[u]) {
        if (ans[v] == -1) {
            ans[v] = ans[u] ^ 1;
            dfs(v);
        } else if (ans[v] == ans[u]) {
            can = false;
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
        adj[u].push_back(v);
        adj[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
        ans[i] = -1;
	}
	for (int i = 0; i < n; i++) {
        if (ans[i] == -1) {
            ans[i] = 0;
            dfs(i);
        }
	}
	if (!can) {
        cout << "IMPOSSIBLE";
	} else {
        for (int i = 0; i < n; i++) {
            cout << ans[i] + 1 << " ";
        }
	}
	return 0;
}
