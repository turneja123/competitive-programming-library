//https://www.codechef.com/problems/WLKLIM3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;

ll dp[N][3];
ll dp_aux[N][2];
vector<int> adj[N];
int ok[N];
int sz[N];
int go[N];

void dfs_subtree(int u, int p) {
    dp[u][0] = 0, dp[u][1] = 0, dp[u][2] = 0;
    dp_aux[u][0] = 0, dp_aux[u][1] = 0;
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
            ok[u] |= ok[v];
            if (ok[v]) {
                go[u] = v;
            }
        }
    }
}

void dfs_dp(int u, int p) {
    vector<int> childs;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_dp(v, u);
        }
        if (v != p && go[u] != v) {
            childs.push_back(v);
            dp_aux[u][0] = (dp_aux[u][0] + (dp_aux[v][0] + 1) + dp_aux[v][1]) % M;
            dp_aux[u][1] = (dp_aux[u][1] + 2 * dp_aux[v][0] + 1) % M;
        }
    }
    ll sum = 0;
    for (int v : childs) {
        dp_aux[u][1] = (dp_aux[u][1] + 2 * (dp_aux[v][0] + 1) * sum) % M;
        dp_aux[u][1] = (dp_aux[u][1] + 2 * dp_aux[v][1] * sum) % M;
        sum = (sum + (dp_aux[v][0] + 1) + dp_aux[v][1] + M) % M;
    }
}

void dfs(int u, int p, int n, ll dp0, ll dp1) {
    if (u == 0) {
        dp[u][0] = 1;
        dp[u][1] = dp_aux[u][0];
        dp[u][2] = dp_aux[u][1];

    } else {
        dp[u][0] = (dp[p][0] + dp[p][1] + dp[p][2]) % M;

        dp[u][1] = ((dp[p][0] + dp[p][1] + dp[p][2]) * dp_aux[u][0]) % M;
        dp[u][1] = (dp[u][1] + dp0 + dp1) % M;

        dp[u][2] = dp[p][0];
        dp[u][2] = (dp[u][2] + 2 * (dp0 + dp1) * dp_aux[u][0]) % M;
        dp[u][2] = (dp[u][2] + (dp[p][0] + dp[p][1] + dp[p][2]) * dp_aux[u][1]) % M;
    }
    if (u == n - 1) {
        return;
    }
    dfs(go[u], u, n, (dp0 + dp[u][0]) % M, (dp1 + dp[u][1] + dp[u][0] * dp_aux[u][0]) % M);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            go[i] = -1;
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        ok[n - 1] = 1;
        dfs_subtree(0, -1);
        dfs_dp(0, -1);
        dfs(0, -1, n, 0, 0);
        cout << dp[n - 1][0] << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            ok[i] = 0;
        }

    }

    return 0;
}
