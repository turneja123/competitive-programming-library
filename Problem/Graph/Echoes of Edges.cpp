//https://repovive.com/contests/5/problems/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

vector<int> adj[2][N];
int deg[2][N];
int dist[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while  (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            adj[0][i].clear();
            adj[1][i].clear();
            deg[0][i] = 0;
            deg[1][i] = 0;
            dist[i] = INF;
        }
        for (int i = 0; i < m; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            u--, v--;
            adj[c][u].push_back(v);
            adj[c][v].push_back(u);
            deg[c][u]++;
            deg[c][v]++;
        }
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (!deg[0][i] || !deg[1][i]) {
                dist[i] = 1;
                q.push(i);
            }
        }
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < 2; c++) {
                for (int v : adj[c][u]) {
                    if (dist[v] == INF) {
                        deg[c][v]--;
                        if (!deg[c][v]) {
                            dist[v] = dist[u] + 1;
                            q.push(v);
                        }
                    }
                }
            }
        }
        if (dist[0] == INF) {
            cout << -1 << endl;
        } else {
            cout << dist[0] << endl;
        }
    }
    return 0;
}
