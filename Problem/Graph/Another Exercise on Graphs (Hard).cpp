//https://codeforces.com/contest/2057/problem/E1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 405;
const int INF = 1e9;

int g[N][N];
int dist[N][N];
vector<int> adj[N];
int ans[N][N][N];
int pref[N][N][N];
bool vis[N];

void bfs(int u, int n) {
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }
    dist[u][u] = 0;
    queue<int> q;
    q.push(u);
    while (q.size()) {
        int x = q.front();
        q.pop();
        if (vis[x]) {
            continue;
        }
        vis[x] = true;
        for (auto y : adj[x]) {
            if (dist[u][y] > dist[u][x] + 1) {
                dist[u][y] = dist[u][x] + 1;
                q.push(y);
            }
        }
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            for (int j = 0; j < n; j++) {
                dist[i][j] = INF;
            }
        }
        vector<tuple<int, int, int>> edges;
        for (int i = 0; i < m; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            edges.push_back(make_tuple(wt, u, v));
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        sort(edges.begin(), edges.end());
        int last = get<0>(edges[edges.size() - 1]);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    ans[i][j][k] = last;
                    pref[i][j][k] = INF;
                }
            }
        }
        for (int j = 0; j < n; j++) {
            bfs(j, n);
        }
        int i = 0;
        while (i < m) {
            vector<pair<int, int>> q;
            while (i < m) {
                auto [wt, x, y] = edges[i];
                if (wt != last) {
                    break;
                }
                q.push_back(make_pair(x, y));
                i++;
            }
            if (i == m) {
                break;
            }
            for (auto [x, y] : q) {
                if (dist[x][y] == 0) {
                    continue;
                }
                dist[x][y] = 0;
                dist[y][x] = 0;
                for (int u = 0; u < n; u++) {
                    for (int v = 0; v < n; v++) {
                        if (u == v) {
                            continue;
                        }
                        dist[u][v] = min({dist[u][v], dist[u][x] + dist[y][v], dist[u][y] + dist[x][v]});
                        pref[u][v][dist[u][v]] = min(pref[u][v][dist[u][v]], last);
                    }
                }
            }
            last = get<0>(edges[i]);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int mn = INF;
                for (int k = 0; k < n; k++) {
                    mn = min(mn, pref[i][j][k]);
                    ans[i][j][k] = min(ans[i][j][k], mn);
                }
            }
        }
        for (int i = 0; i < q; i++) {
            int u, v, k;
            cin >> u >> v >> k;
            u--, v--, k--;
            cout << ans[u][v][k] << " ";
        }
        cout << endl;
    }
    return 0;
}
