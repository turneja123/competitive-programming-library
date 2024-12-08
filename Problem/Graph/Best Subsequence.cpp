//https://codeforces.com/contest/2026/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 200;
const int K = 60;
const int INF = 1e9;

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
    n = K;
    int t;
    cin >> t;
    while (t--) {
        cin >> m;
        for (int i = 1; i <= m; i++) {
            long long a;
            cin >> a;
            for (int j = 0; j < K; j++) {
                long long c = a & (1ll << j);
                if (c) {
                    adj[i].push_back(j + 1 + m);
                }
            }
        }
        int ans = m - bpm();
        cout << ans << endl;
        for (int i = 1; i <= m + K; i++) {
            adj[i].clear();
            pairU[i] = 0;
            pairV[i] = 0;
        }

    }
    return 0;

}
