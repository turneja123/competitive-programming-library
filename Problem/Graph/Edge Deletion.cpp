//https://atcoder.jp/contests/abc243/tasks/abc243_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const long long INF = 1e18;

long long dist[N][N];
long long edge[N][N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INF;
            edge[i][j] = INF;
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
        edge[a][b] = wt;
        edge[b][a] = wt;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (edge[i][j] != INF && edge[i][j] > dist[i][j]) {
                ans++;
            } else if (edge[i][j] != INF) {
                int can = 0;
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j) {
                        continue;
                    }
                    if (dist[i][k] + dist[k][j] <= edge[i][j]) {
                        can = 1;
                    }
                }
                ans += can;
            }
        }
    }
    cout << ans;

    return 0;
}
