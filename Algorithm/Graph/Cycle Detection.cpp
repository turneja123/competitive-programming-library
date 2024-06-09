//https://cses.fi/problemset/task/1678/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

vector<int> adj[N];
vector<int> cycle;
int color[N];
int parent[N];

void dfs(int u, int p) {
    color[u] = 1;
    parent[u] = p;
    for (int v : adj[u]) {
        if (color[v] == 0) {
            dfs(v, u);
        } else if (color[v] == 1) {
            cycle.push_back(v);
            int x = u;
            while (x != v) {
                cycle.push_back(x);
                x = parent[x];
            }
            cycle.push_back(v);
        }
        if (cycle.size()) {
            color[u] = 2;
            return;
        }
    }
    color[u] = 2;
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
	}
	for (int i = 0; i < n && cycle.size() == 0; i++) {
        if (!color[i]) {
            dfs(i, i);
        }
	}
	if (!cycle.size()) {
        cout << "IMPOSSIBLE";
	} else {
        cout << cycle.size() << endl;
        reverse(cycle.begin(), cycle.end());
        for (int u : cycle) {
            cout << u + 1 << " ";
        }
	}
	return 0;
}
