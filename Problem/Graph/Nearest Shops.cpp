//https://www.cses.fi/problemset/task/3303/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 1e9;

int dist[N][2];
int ans[N][2];
int b[N];

vector<int> adj[N];

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
        ans[i][0] = -1;
        ans[i][1] = -1;
    }
    priority_queue<tuple<int, int, int>> pq;
    for (int i = 0; i < k; i++) {
        int u;
        cin >> u;
        u--;
        b[u] = 1;
        dist[u][0] = 0;
        ans[u][0] = u;
        pq.push(make_tuple(0, u, u));
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    while (pq.size()) {
        auto [d, u, s] = pq.top();
        pq.pop();
        d = -d;
        if (dist[u][1] < d) {
            continue;
        }
        for (int v : adj[u]) {
            if (s == v) {
                continue;
            }
            if (dist[v][0] > d + 1) {
                ans[v][0] = s;
                dist[v][0] = d + 1;
                pq.push({-dist[v][0], v, s});
            } else if (s != ans[v][0] && dist[v][1] > d + 1) {
                ans[v][1] = s;
                dist[v][1] = d + 1;
                pq.push({-dist[v][1], v, s});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        int ans = (!b[i] ? dist[i][0] : dist[i][1]);
        if (ans == INF) {
            ans = -1;
        }
        cout << ans << " ";
    }

    return 0;
}
