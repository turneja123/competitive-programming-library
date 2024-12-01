//https://codeforces.com/problemset/problem/1176/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

vector<int> adj[N];
bool vis[N];
int sz[N];
int depth[N];

void dfs(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            depth[v] = depth[u] + 1;
            sz[depth[v]]++;
            dfs(v);
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
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        depth[0] = 0, sz[0] = 1;
        dfs(0);
        int s = 0;
        for (int i = 0; i < n; i += 2) {
            s += sz[i];
        }
        int ans = (s <= n / 2 ? 0 : 1);
        s = (s <= n / 2 ? s : n - s);
        cout << s << endl;
        for (int i = 0; i < n; i++) {
            if (depth[i] % 2 == ans) {
                cout << i + 1 << " ";
            }
            depth[i] = 0, sz[i] = 0, vis[i] = 0;
            adj[i].clear();
        }
        cout << endl;
	}
	return 0;
}
