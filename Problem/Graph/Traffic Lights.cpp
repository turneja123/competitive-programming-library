//https://codeforces.com/contest/2122/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const int INF = 1e9;

vector<int> adj[N];

int deg[N];
int dist[N][2 * N];

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
        for (int i = 0; i < n; i++) {
            deg[i] = adj[i].size();
            for (int j = 0; j < 2 * N; j++) {
                dist[i][j] = INF;
            }
        }
        dist[0][0] = 0;
        for (int j = 0; j < 2 * N - 1; j++) {
            for (int u = 0; u < n; u++) {
                if (dist[u][j] != INF) {
                    dist[adj[u][j % deg[u]]][j + 1] = min(dist[adj[u][j % deg[u]]][j + 1], dist[u][j]);
                    dist[u][j + 1] = min(dist[u][j + 1], dist[u][j] + 1);
                }

            }
        }
        for (int j = 0; j < 2 * N; j++) {
            if (dist[n - 1][j] != INF) {
                cout << j << " " << dist[n - 1][j] << endl;
                break;
            }
        }

        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }
    return 0;
}
