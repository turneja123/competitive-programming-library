//https://codeforces.com/contest/2014/problem/E
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
bool has[N];
long long distu[N][2];
long long distv[N][2];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, h;
        cin >> n >> m >> h;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            has[i] = false;
            distu[i][0] = INF, distu[i][1] = INF;
            distv[i][0] = INF, distv[i][1] = INF;
        }
        for (int i = 0; i < h; i++) {
            int u;
            cin >> u;
            u--;
            has[u] = true;
        }
        for (int i = 0; i < m; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            adj[u].push_back(make_pair(v, wt));
            adj[v].push_back(make_pair(u, wt));
        }
        priority_queue<pair<long long, pair<int, int>>> pq;
        pq.push(make_pair(0, make_pair(0, has[0])));
        distu[0][has[0]] = 0;
        while (pq.size()) {
            int u = pq.top().second.first, flag = pq.top().second.second;
            long long d = -pq.top().first;
            pq.pop();
            if (d != distu[u][flag]) {
                continue;
            }
            for (pair<int, int> p : adj[u]) {
                int v = p.first, wt = p.second;
                long long cur = d + (flag ? wt / 2 : wt);
                int curf = flag | has[v];
                if (distu[v][curf] > cur) {
                    distu[v][curf] = cur;
                    pq.push(make_pair(-cur, make_pair(v, curf)));
                }
            }
        }
        pq.push(make_pair(0, make_pair(n - 1, has[n - 1])));
        distv[n - 1][has[n - 1]] = 0;
        while (pq.size()) {
            int u = pq.top().second.first, flag = pq.top().second.second;
            long long d = -pq.top().first;
            pq.pop();
            if (d != distv[u][flag]) {
                continue;
            }
            for (pair<int, int> p : adj[u]) {
                int v = p.first, wt = p.second;
                long long cur = d + (flag ? wt / 2 : wt);
                int curf = flag | has[v];
                if (distv[v][curf] > cur) {
                    distv[v][curf] = cur;
                    pq.push(make_pair(-cur, make_pair(v, curf)));
                }
            }
        }
        long long ans = INF;
        for (int i = 0; i < n; i++) {
            long long u = min(distu[i][0], distu[i][1]);
            long long v = min(distv[i][0], distv[i][1]);
            if (u != INF && v != INF) {
                ans = min(ans, max(u, v));
            }
        }
        if (ans == INF) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }

    return 0;
}
