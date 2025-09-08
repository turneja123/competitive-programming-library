//https://atcoder.jp/contests/abc422/tasks/abc422_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const ll INF = 1e18;

ll dist[N];
ll sum[N];

int wt[N];
int ct[N];

vector<int> adj[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> wt[i];
        dist[i] = INF;
        sum[i] = INF;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dist[0] = 0;
    sum[0] = wt[0];
    priority_queue<pair<pair<ll, ll>, int>> pq;
    pq.push({{-dist[0], -sum[0]}, 0});
    while (pq.size()) {
        auto [d, w] = pq.top().first;
        d = -d, w = -w;
        int u = pq.top().second;
        pq.pop();
        if ((dist[u] <= d && sum[u] < w) || (dist[u] < d && sum[u] <= w)) {
            continue;
        }
        ct[u]++;
        if (ct[u] > 5000) {
            continue;
        }
        for (int v : adj[u]) {
            ll nxd = d + w;
            ll nxw = w + wt[v];
            if (!(dist[v] <= nxd && sum[v] < nxw) || (dist[v] < nxd && sum[v] <= nxw)) {
                if (dist[v] > nxd) {
                    dist[v] = nxd;
                    sum[v] = nxw;
                } else if (dist[v] == nxd) {
                    sum[v] = min(sum[v], nxw);
                }
                pq.push({{-nxd, -nxw}, v});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << dist[i] << endl;
    }

    return 0;
}
