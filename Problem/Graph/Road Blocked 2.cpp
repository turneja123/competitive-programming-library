//https://atcoder.jp/contests/abc375/tasks/abc375_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18;
const long long M1 = 1e9 + 7, M2 = 998244353;

vector<pair<int, int>> adj[N];
vector<pair<pair<int, int>, int>> edges;

void dijkstra(int u, vector<pair<long long, pair<long long, long long>>> &dist) {
    dist[u] = make_pair(0, make_pair(1, 1));
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push(make_pair(0, u));
    while (pq.size()) {
        int u = pq.top().second; long long d = pq.top().first;
        pq.pop();
        if (d != dist[u].first) {
            continue;
        }
        for (pair<int, int> p : adj[u]) {
            int e = p.second;
            int v = p.first, wt = edges[e].second;
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
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
        edges.push_back(make_pair(make_pair(u, v), wt));
    }
    vector<pair<long long, pair<long long, long long>>> distu(n, {INF, make_pair(0, 0)}), distv(n, {INF, make_pair(0, 0)});
    dijkstra(0, distu);
    dijkstra(n - 1, distv);
    for (int i = 0; i < m; i++) {
        int u = edges[i].first.first, v = edges[i].first.second, wt = edges[i].second;
        pair<long long, long long> edge_ways;
        if (distu[u].first + wt + distv[v].first == distu[n - 1].first) {
            edge_ways = make_pair(distu[u].second.first * distv[v].second.first % M1, distu[u].second.second * distv[v].second.second % M2);
        } else if (distv[u].first + wt + distu[v].first == distu[n - 1].first) {
            edge_ways = make_pair(distv[u].second.first * distu[v].second.first % M1, distv[u].second.second * distu[v].second.second % M2);
        } else {
            edge_ways = make_pair(-1, -1);
        }
        if (edge_ways == distu[n - 1].second) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}
