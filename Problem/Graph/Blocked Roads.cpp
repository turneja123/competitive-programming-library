//https://atcoder.jp/contests/abc218/tasks/abc218_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 405;
const int INF = 1e9;

int dist[N];
bool graph[N][N];
vector<int> adj[N];
vector<int> up[N];

vector<pair<int, int>> edge;

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u][v] = true;
        adj[u].push_back(v);
        edge.push_back(make_pair(u, v));
    }
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[0] = 0;
    queue<int> q;
    q.push(0);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                up[u].push_back(v);
                q.push(v);
            } else if (dist[v] == dist[u] + 1) {
                up[u].push_back(v);
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            dist[j] = INF;
        }
        dist[0] = 0;
        queue<int> q;
        q.push(0);
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int v : up[u]) {
                if (u == edge[i].first && v == edge[i].second) {
                    continue;
                }
                if (dist[v] > dist[u] + 1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
            if (u != edge[i].first && graph[u][edge[i].second] && dist[edge[i].second] > dist[u] + 1) {
                dist[edge[i].second] = dist[u] + 1;
                q.push(edge[i].second);
            }
        }
        if (dist[n - 1] == INF) {
            cout << -1 << endl;
        } else {
            cout << dist[n - 1] << endl;
        }
    }
    return 0;
}
