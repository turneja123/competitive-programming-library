//solution for https://cses.fi/problemset/task/1671/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = LLONG_MAX;
const int N = 1e5 + 5;

ll dist[N];
bool visited[N];
list<pair<int, ll>> adj[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        ll wt;
        cin >> a >> b >> wt;
        a--, b--;
        adj[a].push_back({b, wt});
    }
    priority_queue<pair<ll, int>> pq;
    pq.push({0, 0});
    dist[0] = 0;
    while (pq.size()) {
        int v = pq.top().second;
        pq.pop();
        if (visited[v]) {
            continue;
        }
        visited[v] = true;
        for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
            int u = it->first;
            ll wt = it->second;
            if (wt + dist[v] < dist[u]) {
                dist[u] = wt + dist[v];
                pq.push({-dist[u], u});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            cout << "-1";
        } else {
            cout << dist[i] << " ";
        }
    }
    return 0;

}
