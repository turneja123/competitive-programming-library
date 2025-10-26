//https://www.facebook.com/codingcompetitions/hacker-cup/2025/practice-round
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


const int N = 1e6 + 5;

vector<pair<int, int>> adj[N];
vector<int> edges;
char ans[N];
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

void dfs(int u) {
    while (adj[u].size()) {
        auto [v, e] = adj[u].back();
        adj[u].pop_back();
        if (vis[e]) {
            continue;
        }
        vis[e] = true;
        dfs(v);
        edges.push_back(e);
    }
    return;
}

int main() {
	IOS;
	freopen("1.txt", "r", stdin);
    freopen("2.txt", "w", stdout);
	int t;
	cin >> t;
	for (int tt = 1; tt <= t; tt++) {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> ed;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            ed.push_back({u, v});
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
        int E = m;
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
        ll ct = 0;
        for (int i = 0; i < n; i++) {
            if (id[i] == i) {
                dfs(i);
                if (edges.empty()) {
                    continue;
                }
                int st = 0;
                for (int j = 0; j < edges.size(); j++) {
                    if (edges[j] >= E) {
                        st = j;
                    }
                }
                rotate(edges.begin(), edges.begin() + ((st % edges.size() + edges.size()) % edges.size()), edges.end());
                for (int j = 0; j < edges.size(); j++) {
                    int e = edges[j];

                    if (e < E) {
                        auto [u, v] = ed[e];
                        if (j % 2 == 0) {
                            cola[u]++;
                            cola[v]++;
                            ans[e] = '1';
                        } else {
                            colb[u]++;
                            colb[v]++;
                            ans[e] = '2';
                        }
                    }
                }
                edges.clear();
            }
            ct += (ll)cola[i] * cola[i] + (ll)colb[i] * colb[i];
        }
        cout << "Case #" << tt << ": " << ct << " ";
        for (int i = 0; i < E; i++) {
            cout << ans[i];
        }
        cout << endl;
        for (int i = 0; i <= max(n, m); i++) {
            adj[i].clear();
            cola[i] = 0;
            colb[i] = 0;
            vis[i] = 0;
            vis_comp[i] = 0;
            deg[i] = 0;
            comp[i].clear();
        }
	}
	return 0;
}
