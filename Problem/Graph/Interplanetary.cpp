//https://codeforces.com/gym/102346/problem/I
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 405;
const int Q = 1e5 + 5;
const int INF = 1e9;

int dist[N][N];
int ans[Q];
int a[N];

vector<pair<int, int>> adj[N];

bool compL(int x, int y) {
    return a[x] < a[y];
}

bool compH(int x, int y) {
    return a[x] > a[y];
}

void calc(int n, vector<tuple<int, int, int, int>> &queries, vector<int> &nodes) {
    if (queries.empty()) {
        return;
    }
    sort(queries.begin(), queries.end());

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INF;
        }
    }
    for (int i = 0; i < n; i++) {
        int u = i;
        for (auto [v, wt] : adj[u]) {
            dist[u][v] = min(dist[u][v], wt);
            dist[v][u] = min(dist[v][u], wt);
        }
        dist[i][i] = 0;
    }
    int i = 0, j = 0;
    for (auto [k, x, y, ind] : queries) {
        while (j < k) {
            j++;
            if (i == n) {
                continue;
            }
            int val = a[nodes[i]];
            while (i < n && a[nodes[i]] == val) {
                int u = nodes[i];
                for (int x = 0; x < n; x++) {
                    for (int y = 0; y < n; y++) {
                        dist[x][y] = min({dist[x][y], dist[x][u] + dist[u][y], dist[y][u] + dist[u][x]});
                        dist[y][x] = min({dist[y][x], dist[x][u] + dist[u][y], dist[y][u] + dist[u][x]});
                    }
                }
                i++;
            }
        }
        if (dist[x][y] == INF) {
            ans[ind] = -1;
        } else {
            ans[ind] = dist[x][y];
        }
    }

}

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m;
    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    cin >> q;
    vector<tuple<int, int, int, int>> lo, hi;
    for (int i = 0; i < q; i++) {
        int u, v, k, t;
        cin >> u >> v >> k >> t;
        u--, v--;
        if (t == 0) {
            lo.push_back(make_tuple(k, u, v, i));
        } else {
            hi.push_back(make_tuple(k, u, v, i));
        }
    }
    sort(nodes.begin(), nodes.end(), compL);
    calc(n, lo, nodes);
    sort(nodes.begin(), nodes.end(), compH);
    calc(n, hi, nodes);
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
