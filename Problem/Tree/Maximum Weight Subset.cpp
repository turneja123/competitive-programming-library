//https://codeforces.com/contest/1249/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 205;

vector<int> adj[N];

int a[N];
int depth[N];
int far[N];
int temp[N];
int dp[N][N];

void dfs(int u, int p, int k) {
    far[u] = depth[u];
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u, k);
            for (int i = depth[u]; i <= far[u]; i++) {
                temp[i] = dp[u][i];
            }
            for (int i = depth[u]; i <= far[u]; i++) {
                for (int j = depth[v]; j <= far[v]; j++) {
                    if (i + j - 2 * depth[u] > k) {
                        dp[u][min(i, j)] = max(dp[u][min(i, j)], temp[i] + dp[v][j]);
                    }
                }
            }
            for (int j = depth[v]; j <= far[v]; j++) {
                dp[u][j] = max(dp[u][j], dp[v][j]);
            }
            far[u] = max(far[v], far[u]);
        }
    }
    for (int i = depth[u]; i <= far[u]; i++) {
        if (i - depth[u] > k) {
            dp[u][depth[u]] = max(dp[u][depth[u]], dp[u][i] + a[u]);
        }
    }
    dp[u][depth[u]] = max(dp[u][depth[u]], a[u]);
    return;
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0, k);
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, dp[0][i]);
    }
    cout << ans;



    return 0;
}
