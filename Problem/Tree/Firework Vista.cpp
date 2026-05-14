//https://bubblecup.org/CompetitorsCorner/Problem/FWVISTA
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int h[N];
int up[N];
int x[N], y[N];
int vis[N];
int dp[N][2];

vector<int> adj[N];

int dfs_up(int u) {
    if (vis[u]) {
        return up[u];
    }
    vis[u] = 1;
    up[u] = h[u];
    for (int v : adj[u]) {
        if (h[v] > h[u]) {
            up[u] = max(up[u], dfs_up(v));
        }
    }
    return up[u];
}

void dfs(int u, int p, int m) {
    dp[u][0] = 0;
    dp[u][1] = (up[u] < m ? x[u] : 0) - y[u];
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, m);
            if (h[u] < h[v]) {
                dp[u][0] += max(dp[v][0], dp[v][1]);
                dp[u][1] += dp[v][1];
            } else if (h[u] > h[v]) {
                dp[u][0] += dp[v][0];
                dp[u][1] += max(dp[v][0], dp[v][1]);
            } else {
                int cur = max(dp[v][0], dp[v][1]);
                dp[u][0] += cur;
                dp[u][1] += cur;
            }
        }
    }
}

int main() {
    IOS;
    int n, m, t;
    cin >> n >> m >> t;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        mx = max(mx, h[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < m; i++) {
        int u;
        cin >> u;
        u--;
        x[u]++;
    }
    for (int i = 0; i < t; i++) {
        int u;
        cin >> u;
        u--;
        y[u]++;
    }
    for (int i = 0; i < n; i++) {
        dfs_up(i);
    }

    int l = 1, r = mx, ans = 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        dfs(0, 0, mid);
        if (max(dp[0][0], dp[0][1]) <= 0) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << ans << endl;

    return 0;
}
