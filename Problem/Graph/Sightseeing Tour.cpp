//https://atcoder.jp/contests/abc369/tasks/abc369_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const int E = 2e5 + 5;
const long long INF = 1e18;
long long dist[N][N];

pair<pair<int, int>, int> edges[E];

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m;
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
        dist[a][b] = min(dist[a][b], wt);
        dist[b][a] = min(dist[b][a], wt);
        edges[i] = make_pair(make_pair(a, b), wt);
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        vector<int> e(k);
        for (int j = 0; j < k; j++) {
            cin >> e[j];
            e[j]--;
        }
        long long ans = INF;
        for (int mask = 0; mask < 1 << k; mask++) {
            vector<int> v = e;
            do {
                int u = 0; long long cur = 0;
                for (int j = 0; j < k; j++) {
                    int x = edges[v[j]].first.first, y = edges[v[j]].first.second, wt = edges[v[j]].second;
                    int c = mask & (1 << j);
                    if (c) {
                        cur += dist[u][x] + wt;
                        u = y;
                    } else {
                        cur += dist[u][y] + wt;
                        u = x;
                    }
                }
                cur += dist[u][n - 1];
                ans = min(ans, cur);
            } while (next_permutation(v.begin(), v.end()));
        }
        cout << ans << endl;
    }
    return 0;
}
