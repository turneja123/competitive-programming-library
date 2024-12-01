//https://cses.fi/problemset/task/1195/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const long long INF = 1e18;

vector<pair<int, int>> adj[N];
long long dist[N][2];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        dist[i][0] = INF, dist[i][1] = INF;
    }
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(make_pair(v, wt));
    }
    priority_queue<pair<long long, pair<int, int>>> pq;
    pq.push(make_pair(0, make_pair(0, 0)));
    dist[0][0] = 0;
    while (pq.size()) {
        int u = pq.top().second.first, flag = pq.top().second.second;
        long long d = -pq.top().first;
        pq.pop();
        if (d != dist[u][flag]) {
            continue;
        }
        for (pair<int, int> p : adj[u]) {
            int v = p.first, wt = p.second;
            if (dist[v][flag] > d + wt) {
                dist[v][flag] = d + wt;
                pq.push(make_pair(-dist[v][flag], make_pair(v, flag)));
            }
            if (flag == 0 && dist[v][1] > d + wt / 2) {
                dist[v][1] = d + wt / 2;
                pq.push(make_pair(-dist[v][1], make_pair(v, 1)));
            }
        }
    }
    cout << min(dist[n - 1][0], dist[n - 1][1]) << endl;


    return 0;
}
