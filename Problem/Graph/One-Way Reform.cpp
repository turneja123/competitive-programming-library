//https://codeforces.com/contest/723/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


const int N = 2e5 + 5;

vector<pair<int, int>> adj[N];
vector<pair<int, int>> ans;
vector<int> comp[N];

int deg[N];
bool vis[N];
bool vis_comp[N];
int cola[N];
int colb[N];
int id[N];


void dfs_comp(int u, int j) {
    vis_comp[u] = true;
    id[u] = j;
    if (deg[u] % 2 == 1) {
        comp[j].push_back(u);
    }
    for (auto [v, _] : adj[u]) {
        if (!vis_comp[v]) {
            dfs_comp(v, j);
        }
    }

}

void dfs(int u, int m) {
    while (adj[u].size()) {
        auto [v, e] = adj[u].back();
        adj[u].pop_back();
        if (vis[e]) {
            continue;
        }
        if (e < m) {
            cola[u]++;
            colb[v]++;
            ans.push_back({u, v});
        }
        vis[e] = true;
        dfs(v, m);
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
            adj[u].push_back(make_pair(v, i));
            adj[v].push_back(make_pair(u, i));
            deg[u]++;
            deg[v]++;
        }
        for (int i = 0; i < n; i++) {
            if (!vis_comp[i]) {
                dfs_comp(i, i);
            }
        }
        int e = m;
        for (int i = 0; i < n; i++) {
            if (id[i] == i) {
                for (int j = 0; j < comp[i].size(); j += 2) {
                    int u = comp[i][j], v = comp[i][j + 1];
                    adj[u].push_back(make_pair(v, m));
                    adj[v].push_back(make_pair(u, m));
                    m++;
                }
            }
        }
        int ct = 0;
        for (int i = 0; i < n; i++) {
            if (id[i] == i) {
                dfs(i, e);
            }
            ct += cola[i] == colb[i];
        }
        cout << ct << endl;
        for (auto [u, v] : ans) {
            cout << u + 1 << " " << v + 1 << endl;
        }
        for (int i = 0; i < max(n, m); i++) {
            adj[i].clear();
            cola[i] = 0;
            colb[i] = 0;
            vis[i] = 0;
            vis_comp[i] = 0;
            deg[i] = 0;
            comp[i].clear();
        }
        ans.clear();

	}
	return 0;
}
