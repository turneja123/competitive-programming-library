//https://cses.fi/problemset/task/1196/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

vector<pair<int, int>> adj[N];

multiset<long long> dist[N];

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(make_pair(v, wt));
    }
    dist[0].insert(0);
    priority_queue<pair<long long, int>> pq;
    pq.push(make_pair(0, 0));
    while (pq.size()) {
        int u = pq.top().second; long long d = -pq.top().first;
        pq.pop();
        if (dist[u].find(d) == dist[u].end()) {
            continue;
        }
        for (pair<int, int> p : adj[u]) {
            int v = p.first, wt = p.second;
            if (dist[v].size() < k) {
                dist[v].insert(d + wt);
                pq.push(make_pair(-(d + wt), v));
            } else {
                if (*dist[v].rbegin() > d + wt) {
                    dist[v].erase(dist[v].find(*dist[v].rbegin()));
                    dist[v].insert(d + wt);
                    pq.push(make_pair(-(d + wt), v));
                }
            }
        }
    }
    for (long long d : dist[n - 1]) {
        cout << d << " " ;
    }
    return 0;
}
