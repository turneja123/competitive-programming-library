//https://www.codechef.com/START191A/problems/COLARR7
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const int INF = 1e9;

vector<int> adj[N];
int pairU[N];
int pairV[N];
int dist[N];
int a[N];
int m, n;

bool seen[N];

bool bfs() {
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
                if (dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
    return (dist[0] != INF);
}

bool dfs(int u) {
    if (u != 0) {
        for (auto it = adj[u].begin(); it!= adj[u].end(); ++it) {
            int v = *it;
            if (dist[pairV[v]] == dist[u] + 1) {
                if (dfs(pairV[v]) == true) {
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

int bpm() {
    int res = 0;
    while (bfs()) {
        for (int u = 1; u <= m; u++) {
            if (pairU[u] == 0 && dfs(u)) {
                res++;
            }
        }
    }
    return res;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        m = n;
        int ans = 0;
        for (int i = 1; i <= 2 * n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i <= 2 * n; i += 2) {
            if (a[i] == a[i + 1]) {
                if (!seen[a[i]]) {
                    seen[a[i]] = true;
                } else {
                    ans += 2;
                }
            }
        }
        for (int i = 1, l = 1; i <= 2 * n; i += 2, l++) {
            if (a[i] == a[i + 1]) {
                continue;
            }
            if (!seen[a[i]]) {
                adj[a[i]].push_back(l + m);
            }
            if (!seen[a[i + 1]]) {
                adj[a[i + 1]].push_back(l + m);
            }
            ans += 2;
        }
        ans -= bpm();
        for (int i = 0; i <= 2 * n; i++) {
            adj[i].clear();
            seen[i] = 0;
            pairU[i] = 0;
            pairV[i] = 0;
            dist[i] = 0;
        }
        cout << ans << endl;
    }
    return 0;
}
