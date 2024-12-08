//https://codeforces.com/problemset/problem/1139/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4 + 5;
const int INF = 1e9;

set<int> adj[N];
int pairU[N];
int pairV[N];
int dist[N];
int m, n;

int l[N], r[N], x[N], mark[N], ans[N];

bool bfs(int x) {
    queue <int> q;
    for (int u = 1; u <= m; u++) {
        if (pairU[u] == 0) {
            dist[u] = 0;
            q.push(u);
        } else {
            dist[u] = INF;
        }
    }
    dist[0] = INF;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dist[u] < dist[0]) {
            for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
                int v = *it;

                if (v - m > x) {
                    break;
                }
                if (dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
    return (dist[0] != INF);
}

bool dfs(int u, int x) {
    if (u != 0) {
        for (auto it = adj[u].begin(); it!= adj[u].end(); ++it) {
            int v = *it;

            if (v - m > x) {
                break;
            }
            if (dist[pairV[v]] == dist[u] + 1) {
                if (dfs(pairV[v], x) == true) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int bpm(int x) {
    int res = 0;
    while (bfs(x)) {
        for (int u = 1; u <= m; u++) {
            if (pairU[u] == 0 && dfs(u, x)) {
                res++;
            }
        }
    }
    return res;
}

int main() {
    IOS;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> l[i];
    }
    int k;
    cin >> k;
    for (int i = 1; i <= k; i++) {
        cin >> x[i];
        mark[x[i]] = 1;
    }
    for (int i = 1; i <= n; i++) {
        if (!mark[i]) {
            adj[l[i]].insert(r[i] + 1 + m);
        }
    }
    int j = 1;
    while (j <= m) {
        for (int i = 1; i <= m + j; i++) {
            pairU[i] = 0, pairV[i] = 0;
        }
        int x = bpm(j);
        if (x == j) {
            j++;
        } else {
            break;
        }
    }
    ans[k] = j - 1;
    for (int i = k; i > 1; i--) {
        adj[l[x[i]]].insert(r[x[i]] + 1 + m);
        while (j <= m) {
            for (int i = 1; i <= m + j; i++) {
                pairU[i] = 0, pairV[i] = 0;
            }
            int x = bpm(j);
            if (x == j) {
                j++;
            } else {
                break;
            }
        }
        ans[i - 1] = j - 1;
    }
    for (int i = 1; i <= k; i++) {
        cout << ans[i] << endl;
    }
    return 0;

}
