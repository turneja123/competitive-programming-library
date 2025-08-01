//https://codeforces.com/contest/2053/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
int dist[N];
int dp[N];
int sz[N];
int parent[N];

void dfs(int u, int p) {
    parent[u] = p;
    dist[u] = N;
    dp[u] = 0;
    sz[u] =1 ;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            dp[u] += dp[v];
            sz[u] += sz[v];
            dist[u] = min(dist[u], dist[v] + 1);
        }
    }
    if (adj[u].size() == 1) {
        dist[u] = 0;
    }
    dp[u] += dist[u] <= 1;

}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        if (n == 2) {
            cout << 0 << endl;
        } else {
            int root = 0;
            for (int i = 0; i < n; i++) {
                if (adj[i].size() > 1) {
                    root = i;
                    break;
                }
            }
            dfs(root, root);
            ll ans = 0;
            int leaf = 0;
            for (int i = 0; i < n; i++) {
                if (dist[i] == 0) {
                    leaf++;
                }
            }
            for (int i = 0; i < n; i++) {
                if (dist[i] == 0) {
                    ans += n - leaf;
                }
            }
            for (int u = 0; u < n; u++) {
                if (dist[u] != 0) {
                    for (int v : adj[u]) {
                        if (v != parent[u] && dist[v] == 1) {
                            ans += sz[v] - dp[v];
                        }
                    }
                }
                int all = dp[root];
                if (dist[u] != 0 && u != root && dist[parent[u]] == 1) {
                    ans += (n - sz[u]) - (all - dp[u]);
                }
            }
            cout << ans << endl;
        }
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }

    return 0;
}
