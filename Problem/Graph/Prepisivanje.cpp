//https://evaluator.hsin.hr/events/coci26_6/tasks/HONI252666prepisivanje/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 81;

int a[N][N];
int id[N][N];
int ok[N][N];

const int INF = 1e9;

struct Matching {
    int n, m;

    vector<int> pairU, pairV, dist;
    vector<vector<int>> adj;

    Matching(int _n, int _m) {
        n = _n, m = _m;
        adj.resize(n);
        dist.resize(n);
        pairU.resize(n, -1);
        pairV.resize(m, -1);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < n; u++) {
            if (pairU[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }

        bool f = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] < INF) {
                for (auto v : adj[u]) {
                    if (pairV[v] == -1) {
                        f = true;
                    } else if (dist[pairV[v]] == INF) {
                        dist[pairV[v]] = dist[u] + 1;
                        q.push(pairV[v]);
                    }
                }
            }
        }
        return f;
    }

    bool dfs(int u) {
        if (u != -1) {
            for (auto v : adj[u]) {
                if (pairV[v] == -1 || (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v]))) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    }

    int bpm() {
        for (int i = 0; i < n; i++) {
            pairU[i] = -1;
        }
        for (int i = 0; i < m; i++) {
            pairV[i] = -1;
        }
        while (bfs()) {
            for (int u = 0; u < n; u++) {
                if (pairU[u] == -1) {
                    dfs(u);
                }
            }
        }
        int ans = 0;
        for (int u = 0; u < n; u++) {
            if (pairU[u] != -1) {
                ans++;
            }
        }
        return ans;
    }
};

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    int e = 0, o = 0, add = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            a[i][j] = s[j] - '0';
            add += a[i][j] == 2;
            ok[i][j] = a[i][j] == 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dx) + abs(dy) == 1 && i + dx >= 0 && i + dx < n && j + dy >= 0 && j + dy < m && a[i + dx][j + dy] == 2) {
                        ok[i][j] = 0;
                    }
                }
            }
            if (!ok[i][j]) {
                continue;
            }
            if ((i + j) % 2 == 0) {
                id[i][j] = e++;
            } else {
                id[i][j] = o++;

            }
        }
    }
    Matching mc = Matching(e, o);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i + j) % 2 == 1 || !ok[i][j]) {
                continue;
            }
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dx) + abs(dy) == 1 && i + dx >= 0 && i + dx < n && j + dy >= 0 && j + dy < m && ok[i + dx][j + dy]) {
                        mc.add_edge(id[i][j], id[i + dx][j + dy]);
                    }
                }
            }
        }
    }
    cout << e + o + add - mc.bpm();



    return 0;
}

