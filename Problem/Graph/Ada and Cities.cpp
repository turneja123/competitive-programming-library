//https://www.spoj.com/problems/ADACITY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const int INF = 1e9;

int mat[N][N];
vector<int> adj[N];
int pairU[N];
int pairV[N];
int dist[N];
int m, n;

bool bfs() {
    queue <int> q;
    for (int u = 1; u <= m; u++) {
        if (pairU[u] == 0) {
            dist[u] = 0;
            q.push(u);
        } else {
            dist[u] = INF;
        }
    }
    dist[0] = INF;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dist[u] < dist[0]) {
            for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
                int v = *it;
                if (dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
    return (dist[0] != INF);
}

bool dfs(int u) {
    if (u != 0) {
        for (auto it = adj[u].begin(); it!= adj[u].end(); ++it) {
            int v = *it;
            if (dist[pairV[v]] == dist[u] + 1) {
                if (dfs(pairV[v]) == true) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int bpm() {
    int res = 0;
    while (bfs()) {
        for (int u = 1; u <= m; u++) {
            if (pairU[u] == 0 && dfs(u)) {
                res++;
            }
        }
    }
    return res;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, e, f, tim;
        cin >> n >> e >> f >> tim;
        vector<int> a(f);
        for (int i = 0; i < f; i++) {
            cin >> a[i];
            a[i]--;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                mat[i][j] = INF;
            }
            mat[i][i] = 0;
        }
        for (int i = 0; i < e; i++) {
            int a, b, wt;
            cin >> a >> b >> wt;
            a--, b--;
            mat[a][b] = min(mat[a][b], wt);
            mat[b][a] = min(mat[b][a], wt);
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
                }
            }
        }
        m = f;
        for (int i = 0; i < f; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[a[i]][j] <= tim) {
                    adj[i + 1].push_back(j + 1 + m);
                }
            }
        }
        cout << bpm() << endl;
        for (int i = 0; i <= n + f + 5; i++) {
            adj[i].clear();
            pairU[i] = 0, pairV[i] = 0, dist[i] = 0;
        }
    }
    return 0;
}
