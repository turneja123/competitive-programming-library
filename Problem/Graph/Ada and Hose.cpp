//https://www.spoj.com/problems/ADAHOSE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const ll INF = 1e18;

int a[N][N];
int cost[N * N];
vector<pair<int, int>> adj[N * N];

int id(int i, int j, int m) {
    return 1 + i * m + j;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            cost[id(i, j, n)] = a[i][j];
        }
    }
    int s = 0, t = n * n + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int u = id(i - 1, j, n), v = id(i, j, n);
            if (i == 0) {
                continue;
            }
            adj[u].push_back({v, cost[u] + cost[v]});
            adj[v].push_back({u, cost[u] + cost[v]});
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            int u = id(i, j - 1, n), v = id(i, j, n);
            if (j == 0) {
                u = s;
            } else if (j == n) {
                v = t;
            }
            adj[u].push_back({v, cost[u] + cost[v]});
            adj[v].push_back({u, cost[u] + cost[v]});
        }
    }
    vector<ll> dist(t + 1, INF);
    dist[s] = 0;
    priority_queue<pair<ll, int>> pq;
    pq.push({0, s});
    while (pq.size()) {
        auto [d, u] = pq.top();
        pq.pop();
        d = -d;
        if (d != dist[u]) {
            continue;
        }
        for (auto [v, wt] : adj[u]) {
            if (dist[v] > d + wt) {
                dist[v] = d + wt;
                pq.push({-dist[v], v});
            }
        }
    }
    cout << dist[t];

    return 0;
}
