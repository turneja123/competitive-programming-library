//https://cses.fi/problemset/task/1751
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

vector<int> adj[N];
bool cycle[N];
int color[N];
int parent[N];
int ans[N];

void dfs(int u, int p) {
    color[u] = 1;
    parent[u] = p;
    for (int v : adj[u]) {
        if (color[v] == 0) {
            dfs(v, u);
        } else if (color[v] == 1) {
            vector<int> cyc;
            int x = u;
            while (x != v) {
                cyc.push_back(x);
                x = parent[x];
            }
            cyc.push_back(v);
            for (int x : cyc) {
                ans[x] = cyc.size();
                cycle[x] = true;
            }
        }
        if (!cycle[u]) {
            ans[u] = 1 + ans[v];
        }
    }
    color[u] = 2;
    return;
}

int main() {
	IOS;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
        int u;
        cin >> u;;
        u--;
        adj[i].push_back(u);
	}
	for (int i = 0; i < n; i++) {
        if (!color[i]) {
            dfs(i, i);
        }
	}
	for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
	}
	return 0;
}
