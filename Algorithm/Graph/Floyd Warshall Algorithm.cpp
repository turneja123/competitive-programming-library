//solution for https://cses.fi/problemset/task/1672/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const ll INF = 1e18;
ll dist[N][N];

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
        int a, b;
        ll wt;
        cin >> a >> b >> wt;
        a--, b--;
        dist[a][b] = min(dist[a][b], wt);
        dist[b][a] = min(dist[b][a], wt);
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (dist[a][b] == INF) {
            cout << -1 << endl;
        } else {
            cout << min(dist[a][b], dist[b][a]) << endl;
        }
    }
    return 0;
}
