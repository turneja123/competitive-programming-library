//https://cses.fi/problemset/task/1160
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;
const int K = 20;

vector<int> adj[N];
vector<int> cyc[N];

bool cycle[N];
int color[N];
int parent[N];
int ans[N];

int group[N];
int dist[N];
int entry[N];
int pos[N];

int up[K][N];

void dfs(int u, int p) {
    color[u] = 1;
    parent[u] = p;
    for (int v : adj[u]) {
        if (color[v] == 0) {
            dfs(v, u);
        } else if (color[v] == 1) {
            int x = u;
            while (x != v) {
                cyc[v].push_back(x);
                x = parent[x];
            }
            cyc[v].push_back(v);
            reverse(cyc[v].begin(), cyc[v].end());
            for (int i = 0; i < cyc[v].size(); i++) {
                int x = cyc[v][i];
                cycle[x] = true;
                group[x] = v;
                dist[x] = 0;
                entry[x] = -1;
                pos[x] = i;
            }
        }
        if (!cycle[u]) {
            if (cycle[v]) {
                entry[u] = v;
                dist[u] = 1;
            } else {
                entry[u] = entry[v];
                dist[u] = 1 + dist[v];
            }
        }
    }
    color[u] = 2;
    return;
}

int kth(int u, int d) {
    for (int k = K - 1; k >= 0; k--) {
        int c = d & (1 << k);
        if (c) {
            u = up[k][u];
        }
    }
    return u;
}

int main() {
	IOS;
	int n, q;
	cin >> n >> q;
	for (int i = 0; i < n; i++) {
        int u;
        cin >> u;
        u--;
        adj[i].push_back(u);
	}
	for (int i = 0; i < n; i++) {
        if (!color[i]) {
            dfs(i, i);
        }
        up[0][i] = adj[i][0];
	}
	for (int k = 1; k < K; k++) {
        for (int i = 0; i < n; i++) {
            up[k][i] = up[k - 1][up[k - 1][i]];
        }
	}
	for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (cycle[u] && !cycle[v]) {
            cout << -1 << endl;
        } else if (!cycle[u] && !cycle[v]) {
            if (dist[v] > dist[u]) {
                cout << -1 << endl;
            } else {
                int d = dist[u] - dist[v];
                u = kth(u, d);
                if (u != v) {
                    cout << -1 << endl;
                } else {
                    cout << d << endl;
                }
            }
        } else if (!cycle[u] && cycle[v]) {
            if (group[entry[u]] != group[v]) {
                cout << -1 << endl;
            } else {
                if (pos[entry[u]] <= pos[v]) {
                    cout << dist[u] + pos[v] - pos[entry[u]] << endl;
                } else {
                    cout << dist[u] + cyc[group[v]].size() - (pos[entry[u]] - pos[v]) << endl;
                }
            }
        } else {
            if (group[u] != group[v]) {
                cout << -1 << endl;
            } else {
                if (pos[u] <= pos[v]) {
                    cout << pos[v] - pos[u] << endl;
                } else {
                    cout << cyc[group[v]].size() - (pos[u] - pos[v]) << endl;
                }
            }
        }
	}
	return 0;
}
