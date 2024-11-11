//https://atcoder.jp/contests/abc375/tasks/abc375_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const int Q = 2e5 + 5;
const long long INF = 1e18;

pair<int, int> queries[Q];
vector<pair<pair<int, int>, long long>> edges;
long long dist[N][N];

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INF;
        }
    }
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int a, b; long long wt;
        cin >> a >> b >> wt;
        a--, b--;
        dist[a][b] = wt;
        dist[b][a] = wt;
        edges.push_back(make_pair(make_pair(a, b), wt));
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int e;
            cin >> e;
            e--;
            int a = edges[e].first.first, b = edges[e].first.second;
            dist[a][b] = INF;
            dist[b][a] = INF;
            queries[i] = make_pair(e, -1);
        } else {
            int u, v;
            cin >> u >> v;
            u--, v--;
            queries[i] = make_pair(u, v);
        }

    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    vector<long long> ans;
    for (int i = q - 1; i >= 0; i--) {
        if (queries[i].second == -1) {
            int e = queries[i].first;
            int a = edges[e].first.first, b = edges[e].first.second;
            dist[a][b] = min(dist[a][b], edges[e].second);
            dist[b][a] = min(dist[b][a], edges[e].second);
            for (int u = 0; u < n; u++) {
                for (int v = 0; v < n; v++) {
                    dist[u][v] = min(dist[u][v], dist[u][a] + dist[a][b] + dist[b][v]);
                    dist[u][v] = min(dist[u][v], dist[u][b] + dist[b][a] + dist[a][v]);
                    dist[v][u] = min(dist[v][u], dist[u][v]);
                }
            }
        } else {
            ans.push_back(dist[queries[i].first][queries[i].second]);
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        if (ans[i] == INF) {
            cout << -1 << endl;
        } else {
            cout << ans[i] << endl;
        }
    }

    return 0;
}
