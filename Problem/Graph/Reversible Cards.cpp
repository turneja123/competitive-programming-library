//solution for https://atcoder.jp/contests/arc111/tasks/arc111_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 8e5 + 5;
const int INF = 1e9;

list <int> adj[N];
int pairU[N];
int pairV[N];
int dist[N];
int m, n;

bool bfs();

bool dfs(int u);

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

int main() {
    IOS;
    int e;
    cin >> n;
    m = n; e = n;
    for (int i = 1; i <= e; i++) {
        int a, b;
        cin >> a >> b;
        adj[i].push_back(a + e);
        adj[i].push_back(b + e);
    }
    cout << bpm() << endl;
    return 0;

}
