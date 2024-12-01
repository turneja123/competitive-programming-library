//https://cses.fi/problemset/task/1693/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

vector<int> adj[N];
vector<int> ans;

int in_deg[N];
int out_deg[N];

void dfs(int u) {
    while (adj[u].size()) {
        int v = adj[u].back();
        adj[u].pop_back();
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
        adj[u].push_back(v);
        in_deg[v]++;
        out_deg[u]++;
	}
	bool can = true;
	for (int i = 1; i < n - 1 && can; i++) {
        if (in_deg[i] != out_deg[i]) {
            can = false;
        }
	}
	if (!can || out_deg[0] != in_deg[0] + 1 || out_deg[n - 1] != in_deg[n - 1] - 1) {
        cout << "IMPOSSIBLE";
        return 0;
	}
	dfs(0);
	reverse(ans.begin(), ans.end());
	if (ans.size() != m + 1 || ans.back() != n - 1) {
        cout << "IMPOSSIBLE";
	} else {
        for (int u : ans) {
            cout << u + 1 << " ";
        }
	}
	return 0;
}
