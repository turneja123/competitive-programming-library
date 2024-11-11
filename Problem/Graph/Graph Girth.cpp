//https://cses.fi/problemset/task/1707
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2505;
const int INF = 1e9;

int dist[N];
vector<int> adj[N];

int bfs(int s, int n) {
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;
    queue<pair<int, int>> q;
    q.push(make_pair(s, -1));
    int ans = INF;
    while (q.size()) {
        int u = q.front().first, p = q.front().second;
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(make_pair(v, u));
            } else if (v != p) {
                ans = min(ans, dist[u] + dist[v] + 1);
            }
        }
    }
    return ans;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int ans = INF;
    for (int i = 0; i < n; i++) {
        ans = min(ans, bfs(i, n));
    }
    if (ans == INF) {
        cout << -1;
    } else {
        cout << ans;
    }
    return 0;
}
