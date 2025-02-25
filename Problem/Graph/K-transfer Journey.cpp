//https://www.spoj.com/problems/KTRANS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 55;
const int INF = 1e9;

int dist[N][N][N];
int ans[N][N];
vector<tuple<int, int, int>> adj[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        for (int i = 0; i < m; i++) {
            int u, v, wt, f;
            cin >> u >> v >> wt >> f;
            u--, v--;
            adj[u].push_back(make_tuple(v, wt, f));
        }
        for (int st = 0; st < n; st++) {
            for (int j = 0; j < n; j++) {
                for (int c = 0; c <= k; c++)  {
                    dist[st][j][c] = INF;
                }
            }
            priority_queue<tuple<int, int, int>> pq;
            pq.push(make_tuple(0, st, 0));
            dist[st][st][0] = 0;
            while (pq.size()) {
                auto [wt, u, c] = pq.top();
                wt = -wt;
                pq.pop();
                if (wt != dist[st][u][c] || c == k) {
                    continue;
                }
                for (auto [v, d, f] : adj[u]) {
                    if (wt <= f && dist[st][v][c + 1] >= wt + d) {
                        dist[st][v][c + 1] = wt + d;
                        pq.push(make_tuple(-dist[st][v][c + 1], v, c + 1));
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            for (int j = 0; j < n; j++) {
                ans[i][j] = INF;
                for (int c = 0; c <= k; c++) {
                    ans[i][j] = min(ans[i][j], dist[i][j][c]);
                }
                cout << ((ans[i][j] == INF) ? -1 : ans[i][j]) << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
