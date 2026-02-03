//https://ocpc2026w.eolymp.space/en/compete/ig3v7lohgt0vd43nv48bk2lb4o/problem/2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

const int N = 1005;
const ll INF = 1e18;


int costl[N][N];
int costd[N][N];
vector<pair<int, int>> adj[N * N];

int id(int i, int j, int m) {
    return 1 + i * (m - 1) + j;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    int n, m, k;
    cin >> n >> m >> k;
    int s = 0, t = (n - 1) * (m - 1) + 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            cin >> costl[i][j];
            int u = id(i - 1, j, m), v = id(i, j, m);
            if (i == 0) {
                u = s;
            } else if (i == n - 1) {
                v = t;
            }
            adj[u].push_back({v, costl[i][j]});
            adj[v].push_back({u, costl[i][j]});
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            cin >> costd[i][j];
            int u = id(i, j - 1, m), v = id(i, j, m);
            if (j == 0) {
                u = s;
            } else if (j == m - 1) {
                v = t;
            }

            adj[u].push_back({v, costd[i][j]});
            adj[v].push_back({u, costd[i][j]});
        }
    }
    vector<ll> dist(t + 1, INF);
    dist[s] = 0;
    priority_queue<pair<ll, int>> pq;
    pq.push({0, s});
    while (pq.size()) {
        auto [d, u] = pq.top();
        pq.pop();
        d = -d;
        if (d != dist[u]) {
            continue;
        }
        for (auto [v, wt] : adj[u]) {
            if (dist[v] > d + wt) {
                dist[v] = d + wt;
                pq.push({-dist[v], v});
            }
        }
    }
    cout << (ld)k / (ld)dist[t];

    return 0;
}
