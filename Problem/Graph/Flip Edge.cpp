//https://atcoder.jp/contests/abc395/tasks/abc395_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18;

vector<int> adj[N];
vector<int> rev[N];

long long dist[N][2];


int main() {
    IOS;
    int n, m, x;
    cin >> n >> m >> x;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        rev[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }
    dist[0][0] = 0;
    priority_queue<pair<long long, pair<int, int>>> pq;
    pq.push(make_pair(0, make_pair(0, 0)));
    while (pq.size()) {
        long long wt = -pq.top().first;
        int u = pq.top().second.first, f = pq.top().second.second;
        pq.pop();
        if (dist[u][f] != wt) {
            continue;
        }
        if (f == 0) {
            for (int v : adj[u]) {
                if (dist[v][0] > dist[u][0] + 1) {
                    dist[v][0] = dist[u][0] + 1;
                    pq.push(make_pair(-dist[v][0], make_pair(v, 0)));
                }
            }
            for (int v : rev[u]) {
                if (dist[v][1] > dist[u][0] + 1 + x) {
                    dist[v][1] = dist[u][0] + 1 + x;
                    pq.push(make_pair(-dist[v][1], make_pair(v, 1)));
                }
            }
        } else {
            for (int v : adj[u]) {
                if (dist[v][0] > dist[u][1] + 1 + x) {
                    dist[v][0] = dist[u][1] + 1 + x;
                    pq.push(make_pair(-dist[v][0], make_pair(v, 0)));
                }
            }
            for (int v : rev[u]) {
                if (dist[v][1] > dist[u][1] + 1) {
                    dist[v][1] = dist[u][1] + 1;
                    pq.push(make_pair(-dist[v][1], make_pair(v, 1)));
                }
            }
        }
    }
    cout << min(dist[n - 1][0], dist[n - 1][1]);
    return 0;
}
