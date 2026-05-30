//https://codeforces.com/contest/2231/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;

int lca[N][N];
int depth[N];
int ct[N];

vector<int> adj[N];
vector<int> subtree[N];

void dfs(int u, int p, int d, int n, ll &ans) {
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u, d, n, ans);
            for (int k : subtree[v]) {
                subtree[u].push_back(k);
            }
            for (int i = 0; i <= n; i++) {
                lca[u][i + 1] += lca[v][i];
            }
        }
    }
    for (int v : subtree[u]) {
        lca[u][depth[v] - depth[u] + 1]++;
    }
    for (int x : adj[u]) {
        if (x == p) {
            continue;
        }
        for (int y : adj[u]) {
            if (x == y || y == p) {
                continue;
            }
            for (int xx : subtree[x]) {
                for (int yy : subtree[y]) {
                    if (xx < yy) {
                        lca[u][depth[xx] + depth[yy] - 2 * depth[u] + 1]++;
                    }
                }
            }
        }
    }
    for (int x : adj[u]) {
        if (x == p) {
            continue;
        }
        for (int xx : subtree[x]) {
            ct[depth[xx] - depth[u]]++;
        }
    }
    ll contrib = 0;
    for (int x : adj[u]) {
        if (x == p) {
            continue;
        }
        for (int xx : subtree[x]) {
            ct[depth[xx] - depth[u]]--;
        }
        for (int i = 1; i <= n; i++) {
            int val = i + 1;
            if (val == d) {
                ans += lca[x][i];
            }
            if (val < d) {
                ans += (ll)lca[x][i] * ct[d - val];
            }
        }
        for (int y : adj[u]) {
            if (y == p || y <= x) {
                continue;
            }
            for (int yy : subtree[y]) {
                ct[depth[yy] - depth[u]]--;
            }

            for (int xx : subtree[x]) {
                for (int yy : subtree[y]) {
                    int val = depth[xx] + depth[yy] - 2 * depth[u] + 1;
                    if (val == d) {
                        ans++;
                    }
                    if (val < d) {
                        contrib += ct[d - val];
                    }
                }
            }
            for (int yy : subtree[y]) {
                ct[depth[yy] - depth[u]]++;
            }
        }
        for (int xx : subtree[x]) {
            ct[depth[xx] - depth[u]]++;
        }
    }
    ans += contrib / 3;
    for (int x : adj[u]) {
        if (x == p) {
            continue;
        }
        for (int xx : subtree[x]) {
            ct[depth[xx] - depth[u]]--;
        }
    }
    subtree[u].push_back(u);
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, d;
        cin >> n >> d;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        ll ans = 0;
        dfs(0,0, d, n, ans);
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            subtree[i].clear();
            adj[i].clear();
            for (int j = 0; j <= n; j++) {
                lca[i][j] = 0;
            }
        }
    }

    return 0;
}
