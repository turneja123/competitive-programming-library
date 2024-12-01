//https://cses.fi/problemset/task/1202/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const int M = 1e9 + 7;
const long long INF = 1e18;

vector<pair<int, int>> adj[N];

tuple<long long, long long, int, int> dist[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(make_pair(v, wt));
    }
    for (int i = 0; i < n; i++) {
        dist[i] = make_tuple(INF, 0, INF, 0);
    }
    dist[0] = make_tuple(0, 1, 0, 0);
    priority_queue<pair<long long, int>> pq;
    pq.push(make_pair(0, 0));
    while (pq.size()) {
        long long cur = -pq.top().first; int u = pq.top().second;
        pq.pop();
        auto [d, ways, mn, mx] = dist[u];
        if (cur != d) {
            continue;
        }
        for (pair<int, int> p : adj[u]) {
            int v = p.first, wt = p.second;
            if (get<0>(dist[v]) > d + wt) {
                dist[v] = make_tuple(d + wt, ways, mn + 1, mx + 1);
                pq.push(make_pair(-(d + wt), v));
            } else if (get<0>(dist[v]) == d + wt) {
                get<1>(dist[v]) = (get<1>(dist[v]) + ways) % M;
                get<2>(dist[v]) = min(get<2>(dist[v]), mn + 1);
                get<3>(dist[v]) = max(get<3>(dist[v]), mx + 1);
            }
        }
    }
    auto [d, ways, mn, mx] = dist[n - 1];
    cout << d << " " << ways << " " << mn << " " << mx;
    return 0;
}
