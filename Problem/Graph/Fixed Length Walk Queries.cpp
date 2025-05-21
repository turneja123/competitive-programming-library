//https://cses.fi/problemset/submit/3357/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const int INF = 1e9;

int dist[N][N][2];
vector<int> adj[N];

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int st = 0; st < n; st++) {
        for (int i = 0; i < n; i++) {
            dist[st][i][0] = INF;
            dist[st][i][1] = INF;
        }
        dist[st][st][0] = 0;
        queue<tuple<int, int, int>> pq;
        pq.push(make_tuple(0, st, 0));
        while (pq.size()) {
            auto [d, u, f] = pq.front();
            pq.pop();
            for (int v : adj[u]) {
                if (dist[st][v][(f + 1) % 2] > dist[st][u][f] + 1) {
                    dist[st][v][(f + 1) % 2] = dist[st][u][f] + 1;
                    pq.push(make_tuple(-dist[st][v][(f + 1) % 2], v, (f + 1) % 2));
                }
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        u--, v--;
        if (dist[u][v][x % 2] <= x) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }


    return 0;
}
