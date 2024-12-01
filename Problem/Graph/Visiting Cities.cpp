//https://cses.fi/problemset/task/1203
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18;
const long long M1 = 1e9 + 7, M2 = 998244352;

vector<pair<int, int>> adj[2][N];

void dijkstra(int u, vector<pair<long long, pair<long long, long long>>> &dist, int f) {
    dist[u] = make_pair(0, make_pair(1, 1));
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push(make_pair(0, u));
    while (pq.size()) {
        int u = pq.top().second; long long d = pq.top().first;
        pq.pop();
        if (d != dist[u].first) {
            continue;
        }
        for (pair<int, int> p : adj[f][u]) {
            int v = p.first, wt = p.second;
            if (dist[v].first > dist[u].first + wt) {
                dist[v].first = dist[u].first + wt;
                dist[v].second = dist[u].second;
                pq.push(make_pair(dist[v].first, v));
            } else if (dist[v].first == dist[u].first + wt) {
                dist[v].second.first = (dist[v].second.first + dist[u].second.first) % M1;
                dist[v].second.second = (dist[v].second.second + dist[u].second.second) % M2;
            }
        }
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[0][u].push_back(make_pair(v, wt));
        adj[1][v].push_back(make_pair(u, wt));
    }
    vector<pair<long long, pair<long long, long long>>> distu(n, {INF, make_pair(0, 0)}), distv(n, {INF, make_pair(0, 0)});
    dijkstra(0, distu, 0);
    dijkstra(n - 1, distv, 1);
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        pair<long long, long long> ways;
        if (distu[i].first + distv[i].first == distu[n - 1].first) {
            ways = make_pair(distu[i].second.first * distv[i].second.first % M1, distu[i].second.second * distv[i].second.second % M2);
        } else {
            ways = make_pair(-1, -1);
        }
        if (ways == distu[n - 1].second) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for (int u : ans) {
        cout << u + 1 << " ";
    }

    return 0;
}
