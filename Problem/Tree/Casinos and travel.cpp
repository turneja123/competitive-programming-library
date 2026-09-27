//https://codeforces.com/contest/852/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const ll M = 1e9 + 7;

vector<int> adj[N];

ll dp_subtree[N][2][2];
ll dp[N][2];
ll pref[N][2];
ll suf[N][2];

void dfs(int u, int p) {
    int leaf = 1;
    ll ways[2];
    ways[0] = 1, ways[1] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            ways[0] = ways[0] * (dp_subtree[v][0][0] + dp_subtree[v][0][1]) % M;
            ways[1] = ways[1] * (dp_subtree[v][1][0] + dp_subtree[v][1][1]) % M;
            leaf = 0;
        }
    }
    if (!leaf) {
        dp_subtree[u][0][0] = ways[0];
        dp_subtree[u][1][0] = ways[1];
        dp_subtree[u][0][1] = ways[1];
        dp_subtree[u][1][1] = ways[0];
    } else {
        dp_subtree[u][0][0] = 1;
        dp_subtree[u][1][1] = 1;
    }
}

ll ans = 0;

void dfs_dp(int u, int p) {

    vector<int> child;
    for (int v : adj[u]) {
        if (v != p) {
            child.push_back(v);
        }
    }
    int n = child.size();
    if (!n) {
        return;
    }
    for (int i = 0; i < n; i++) {
        int v = child[i];
        pref[i][0] = (i == 0 ? 1 : pref[i - 1][0]) * (dp_subtree[v][0][0] + dp_subtree[v][0][1]) % M;
        pref[i][1] = (i == 0 ? 1 : pref[i - 1][1]) * (dp_subtree[v][1][0] + dp_subtree[v][1][1]) % M;
    }
    for (int i = n - 1; i >= 0; i--) {
        int v = child[i];
        suf[i][0] = (i == n - 1 ? 1 : suf[i + 1][0]) * (dp_subtree[v][0][0] + dp_subtree[v][0][1]) % M;
        suf[i][1] = (i == n - 1 ? 1 : suf[i + 1][1]) * (dp_subtree[v][1][0] + dp_subtree[v][1][1]) % M;
    }


    for (int i = 0; i < n; i++) {
        int v = child[i];

        ll prod[2] = {};
        prod[0] = (i == 0 ? 1 : pref[i - 1][0]) * (i == n - 1 ? 1 : suf[i + 1][0]) % M;
        prod[1] = (i == 0 ? 1 : pref[i - 1][1]) * (i == n - 1 ? 1 : suf[i + 1][1]) % M;

        ll d0 = (u == 0 ? 1 : dp[u][0]);
        ll d1 = (u == 0 ? 1 : dp[u][1]);

        dp[v][0] = (prod[0] * d0) % M;
        dp[v][1] = (prod[0] * d0) % M;

        if (!(u == 0 && n == 1)) {
            dp[v][0] = (prod[0] * d0 + prod[1] * d1) % M;
            dp[v][1] = (prod[0] * d0 + prod[1] * d1) % M;
        }

        ans = (ans + dp_subtree[v][0][0] * dp[v][0] + (adj[v].size() == 1 ? 1 : dp_subtree[v][0][1]) * dp[v][1]) % M;
    }

    for (int i = 0; i < n; i++) {
        int v = child[i];
        dfs_dp(v, u);
    }

}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    dfs_dp(0, 0);
    ans = (ans + dp_subtree[0][0][0] + dp_subtree[0][0][1]) % M;
    cout << ans;

    return 0;
}
