//https://codeforces.com/contest/2040/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;

vector<int> adj[N];
long long dp[N][N];
int parent[N];
int deg[N];

void dfs(int u, int n) {
    if (u == 0) {
        for (int i = 0; i <= n; i++) {
            dp[u][i] = 0;
        }
    } else if (parent[u] == 0) {
        for (int i = 0; i <= n; i++) {
            dp[u][i] = 2 * deg[u] - 1;
            if (i != 0) {
                dp[u][i] = min(dp[u][i], 1ll);
            }
        }
    } else {
        for (int i = 0; i <= n; i++) {
            dp[u][i] = dp[parent[parent[u]]][i] + 2 * deg[u];
            if (i != 0) {
                dp[u][i] = min(dp[u][i], dp[parent[parent[u]]][i - 1] + 2);
            }
        }
    }
    for (int v : adj[u]) {
        if (parent[u] != v) {
            parent[v] = u;
            dfs(v, n);
        }
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[v]++;
            deg[u]++;
        }
        parent[0] = 0;
        dfs(0, n);
        for (int i = 0; i < q; i++) {
            int v, p;
            cin >> v >> p;
            v--;
            cout << dp[parent[v]][p] + 1<< endl;
        }
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            deg[i] = 0;
        }
    }
    return 0;
}
