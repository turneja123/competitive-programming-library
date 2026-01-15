//https://atcoder.jp/contests/arc212/tasks/arc212_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll INF = 1e18;

ll dist[N];
vector<pair<int, int>> adj[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    int ok = 0; ll d = 0;
    int st, en;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        if (i == 0) {
            st = v, en = u;
            if (st == en) {
                ok = 1;
            }
            d = w;
        } else {
            adj[u].push_back({v, w});
        }
    }
    if (ok) {
        cout << d;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[st] = d;
    priority_queue<pair<ll, int>> pq;
    pq.push({-d, st});
    while (pq.size()) {
        auto [d, u] = pq.top();
        d = -d;
        pq.pop();
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
    if (dist[en] == INF) {
        cout << -1;
    } else {
        cout << dist[en];
    }

    return 0;
}
