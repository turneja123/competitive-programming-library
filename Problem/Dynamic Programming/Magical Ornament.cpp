//solution for https://atcoder.jp/contests/abc190/tasks/abc190_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int M = 17;
const int INF = 1e9 + 5;

list<int> adj[N];

int c[M];
int dist[M][N];
int dp[M][1 << M];
bool visited[M][N];
bool b[N];

void dijkstra(int k) {
    for (int i = 0; i < N; i++) {
        dist[k][i] = INF;
    }
    priority_queue<pair<ll, int>> pq;
    pq.push({0, c[k]});
    dist[k][c[k]] = 0;
    while (pq.size()) {
        int v = pq.top().second;
        pq.pop();
        if (visited[k][v]) {
            continue;
        }
        visited[k][v] = true;
        for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
            int u = *it;
            if (1 + dist[k][v] < dist[k][u]) {
                dist[k][u] = 1 + dist[k][v];
                pq.push({-dist[k][u], u});
            }
        }
    }

}


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> c[i];
        c[i]--;
    }
    if (k == 1) {
        cout << 1;
        return 0;
    }
    for (int i = 0; i < k; i++) {
        dijkstra(i);
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < 1 << k; j++) {
            dp[i][j] = INF;
            if (j == 1 << i) {
                dp[i][j] = 0;
            }
        }
    }
    int ans = INF;
    for (int j = 0; j < 1 << k; j++){
        for (int p = 0; p < k; p++) {
            for (int i = 0; i < k; i++) {
                if (i == p || (int)(j & (1 << i)) == 0 || (int)(j & (1 << p)) == 0) {
                    continue;
                }
                dp[p][j] = min(dp[p][j], dp[i][j ^ (1 << p)] + dist[p][c[i]]);
                if (j == (1 << k) - 1) {
                    ans = min(ans, dp[p][j]);
                }
            }
        }
    }
    if (ans == INF) {
        cout << -1;
    } else {
        cout << ans + 1;
    }
    return 0;
}
