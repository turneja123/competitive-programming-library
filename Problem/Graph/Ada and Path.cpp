//https://www.spoj.com/problems/ADAPATH/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e4 + 5;
const int K = 10;
const int INF = 1e9;

vector<int> adj[K][N];
int pairU[N];
int pairV[N];
int dist[N];
int m, n;
int ind[N][N];

bool bfs(int x) {
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
            for (auto it = adj[x][u].begin(); it != adj[x][u].end(); ++it) {
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

bool dfs(int u, int x) {
    if (u != 0) {
        for (auto it = adj[x][u].begin(); it!= adj[x][u].end(); ++it) {
            int v = *it;
            if (dist[pairV[v]] == dist[u] + 1) {
                if (dfs(pairV[v], x) == true) {
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

int bpm(int x) {
    int res = 0;
    while (bfs(x)) {
        for (int u = 1; u <= m; u++) {
            if (pairU[u] == 0 && dfs(u, x)) {
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
        int dim;
        cin >> dim;
        vector<vector<int>> a(dim, vector<int>(dim, 0));
        vector<int> ct(10, 0);
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                cin >> a[i][j];
                a[i][j]--;
                ind[i][j] = ct[a[i][j]];
                ct[a[i][j]]++;
            }
        }
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (abs(dx) + abs(dy) == 1 && i + dx >= 0 && i + dx < dim && j + dy >= 0 && j + dy < dim && a[i][j] == a[i + dx][j + dy] - 1) {
                            adj[a[i][j]][ind[i][j] + 1].push_back(ct[a[i][j]] + ind[i + dx][j + dy] + 1);
                        }
                    }
                }
            }
        }
        bool can = true;
        for (int i = 0; i < 9 && can; i++) {
            if (ct[i] < ct[i + 1]) {
                can = false;
            } else {
                for (int j = 0; j <= ct[i] + ct[i + 1]; j++) {
                    pairU[j] = 0;
                    pairV[j] = 0;
                }
                m = ct[i];
                int sz = bpm(i);
                if (sz < ct[i + 1]) {
                    can = false;
                }
            }
        }
        if (can) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
        for (int i = 0; i < 10; i++) {
            ct[i] = 0;
        }
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                adj[a[i][j]][ct[a[i][j]] + 1].clear();
                ct[a[i][j]]++;
            }
        }
    }
    return 0;

}
