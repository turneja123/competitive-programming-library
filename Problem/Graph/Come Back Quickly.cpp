//https://atcoder.jp/contests/abc191/tasks/abc191_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const int INF = 2e9;

int dist[N][N];
int ans[N];

vector<pair<int, int>> adj[N];
vector<pair<int, int>> rev[N];


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INF;
        }
        ans[i] = INF;
    }
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        if (u == v) {
            ans[u] = min(ans[u], wt);
            continue;
        }
        adj[u].emplace_back(v, wt);
        rev[v].emplace_back(u, wt);
    }

    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        priority_queue<pair<int, int>> pq;
        pq.push(make_pair(0, i));
        while (pq.size()) {
            auto [d, u] = pq.top();
            d = -d;
            pq.pop();
            if (d != dist[i][u]) {
                continue;
            }
            for (auto [v, wt] : adj[u]) {
                if (dist[i][v] > dist[i][u] + wt) {
                    dist[i][v] = dist[i][u] + wt;
                    pq.push(make_pair(-dist[i][v], v));
                }
            }
        }
        for (auto [v, wt] : rev[i]) {
            ans[i] = min(ans[i], dist[i][v] + wt);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << (ans[i] == INF ? -1 : ans[i]) << endl;
    }


    return 0;
}
