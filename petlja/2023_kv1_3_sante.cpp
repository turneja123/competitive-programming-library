#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int dist[N][2];
bool visited[N][2];
list<pair<int, int>> adj[N];

int main() {
    IOS;
    int n, m, x, y, ans = N;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    cin >> x >> y;
    x--, y--;

    for (int i = 0; i < n; i++) {
        dist[i][0] = N;
        dist[i][1] = N;
    }
    dist[x][0] = 0;
    priority_queue<pair<int, pair<int, int>>> pq;
    pq.push(make_pair(dist[x][0], make_pair(0, x)));
    while (!pq.empty()) {
        int w = (pq.top()).second.first;
        int u = (pq.top()).second.second;
        pq.pop();
        if (visited[u][w]) {
            continue;
        }
        visited[u][w] = true;
        if (u == y) {
            ans = min(ans, dist[u][w]);
            continue;
        }
        for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
            int v = it->first, wv = it->second;
            int d = dist[u][w] + abs(wv - w);
            if (!visited[v][wv] && d < dist[v][wv]) {
                dist[v][wv] = d;
                pq.push(make_pair(-d, make_pair(wv, v)));
            }
        }
    }
    if (ans == N) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }



    return 0;
}
