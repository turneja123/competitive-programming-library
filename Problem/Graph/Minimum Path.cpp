//solution for https://codeforces.com/contest/1473/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll INF = 1e18;

list<pair<int, int>> adj[N];
ll dist[N][2][2];
bool vis[N][2][2];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        ll wt;
        cin >> a >> b >> wt;
        a--, b--;
        adj[a].push_back({b, wt});
        adj[b].push_back({a, wt});
    }
    for (int i = 0; i < n; i++) {
        dist[i][0][0] = INF;
        dist[i][0][1] = INF;
        dist[i][1][0] = INF;
        dist[i][1][1] = INF;
    }
    priority_queue<pair<ll, array<int, 3>>> pq;
    dist[0][0][0] = 0;
    pq.push({0, {0, 0, 0}});
    while (pq.size()) {
        array<int, 3> a = pq.top().second;
        int v = a[0], mn = a[1], mx = a[2];
        pq.pop();
        if (vis[v][mn][mx]) {
            continue;
        }
        vis[v][mn][mx] = true;
        for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
            int u = it->first;
            ll wt = it->second;
            if (!vis[u][0][0]) {
                if (mn == 0 && mx == 0) {
                    if (dist[u][0][0] > dist[v][mn][mx] + wt) {
                        dist[u][0][0] = dist[v][mn][mx] + wt;
                        pq.push({-dist[u][0][0], {u, 0, 0}});
                    }
                }
            }
            if (!vis[u][0][1]) {
                if (mn == 0 && mx == 0) {
                    if (dist[u][0][1] > dist[v][mn][mx]) {
                        dist[u][0][1] = dist[v][mn][mx];
                        pq.push({-dist[u][0][1], {u, 0, 1}});
                    }
                }
                if (mn == 0 && mx == 1) {
                    if (dist[u][0][1] > dist[v][mn][mx] + wt) {
                        dist[u][0][1] = dist[v][mn][mx] + wt;
                        pq.push({-dist[u][0][1], {u, 0, 1}});
                    }
                }
            }
            if (!vis[u][1][0]) {
                if (mn == 0 && mx == 0) {
                    if (dist[u][1][0] > dist[v][mn][mx] + 2ll * wt) {
                        dist[u][1][0] = dist[v][mn][mx] + 2ll * wt;
                        pq.push({-dist[u][1][0], {u, 1, 0}});
                    }
                }
                if (mn == 1 && mx == 0) {
                    if (dist[u][1][0] > dist[v][mn][mx] + wt) {
                        dist[u][1][0] = dist[v][mn][mx] + wt;
                        pq.push({-dist[u][1][0], {u, 1, 0}});
                    }
                }
            }
            if (!vis[u][1][1]) {
                if (mn == 0 && mx == 0) {
                    if (dist[u][1][1] > dist[v][mn][mx] + wt) {
                        dist[u][1][1] = dist[v][mn][mx] + wt;
                        pq.push({-dist[u][1][1], {u, 1, 1}});
                    }
                }
                if (mn == 0 && mx == 1) {
                    if (dist[u][1][1] > dist[v][mn][mx] + 2ll * wt) {
                        dist[u][1][1] = dist[v][mn][mx] + 2ll * wt;
                        pq.push({-dist[u][1][1], {u, 1, 1}});
                    }
                }
                if (mn == 1 && mx == 0) {
                    if (dist[u][1][1] > dist[v][mn][mx]) {
                        dist[u][1][1] = dist[v][mn][mx];
                        pq.push({-dist[u][1][1], {u, 1, 1}});
                    }
                }
                if (mn == 1 && mx == 1) {
                    if (dist[u][1][1] > dist[v][mn][mx] + wt) {
                        dist[u][1][1] = dist[v][mn][mx] + wt;
                        pq.push({-dist[u][1][1], {u, 1, 1}});
                    }
                }
            }
        }
    }
    for (int i = 1; i < n; i++)
        cout << dist[i][1][1] << " ";
    return 0;
}
