//https://codeforces.com/contest/1882/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 20;

vector<int> adj[N];

int a[N];
int sz[N];
long long subtree[K][N][2];
long long dp[K][N][2];

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_subtree(v, u);
            for (int k = 0; k < K; k++) {
                int c = a[u] & (1 << k);
                if (c) {
                    subtree[k][u][0] += subtree[k][v][1];
                    subtree[k][u][1] += subtree[k][v][1];
                } else {
                    subtree[k][u][0] += subtree[k][v][0];
                    subtree[k][u][1] += subtree[k][v][0];
                }
            }
            sz[u] += sz[v];
        }
    }
    for (int k = 0; k < K; k++) {
        int c = a[u] & (1 << k);
        if (c) {
            subtree[k][u][0] += (long long)sz[u] * (1 << k);
            subtree[k][u][1] += 0;
        } else {
            subtree[k][u][0] += 0;
            subtree[k][u][1] += (long long)sz[u] * (1 << k);
        }
    }
    return;
}

void dfs(int u, int p, int n) {

    long long sum[K][2];
    for (int k = 0; k < K; k++) {
        sum[k][0] = 0;
        sum[k][1] = 0;
    }
    for (int v : adj[u]) {
        if (v != p) {
            for (int k = 0; k < K; k++) {
                sum[k][0] += subtree[k][v][0];
                sum[k][1] += subtree[k][v][1];
            }
        }
    }

    for (int v : adj[u]) {
        if (v != p) {
            for (int k = 0; k < K; k++) {
                sum[k][0] -= subtree[k][v][0];
                sum[k][1] -= subtree[k][v][1];
                int c = a[u] & (1 << k);
                if (c) {
                    dp[k][v][0] = dp[k][u][1] + sum[k][1] + (long long)(n - sz[v]) * (1 << k);
                    dp[k][v][1] = dp[k][u][1] + sum[k][1];
                } else {
                    dp[k][v][0] = dp[k][u][0] + sum[k][0];
                    dp[k][v][1] = dp[k][u][0] + sum[k][0] + (long long)(n - sz[v]) * (1 << k);
                }
                sum[k][0] += subtree[k][v][0];
                sum[k][1] += subtree[k][v][1];
            }

            dfs(v, u, n);
        }
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
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
        dfs_subtree(0, 0);
        dfs(0, 0, n);
        for (int i = 0; i < n; i++) {
            long long ans = 0;
            for (int k = 0; k < 20; k++) {
                int c = a[i] & (1 << k);
                if (c) {
                    ans += subtree[k][i][1] + dp[k][i][1];
                } else {
                    ans += subtree[k][i][0] + dp[k][i][0];
                }
                //ans += min(subtree[k][i][0] + dp[k][i][0], subtree[k][i][1] + dp[k][i][1]);
                subtree[k][i][0] = 0, subtree[k][i][1] = 0;
                dp[k][i][0] = 0, dp[k][i][1] = 0;
            }
            cout << ans << " ";
            adj[i].clear();
        }
        cout << endl;
    }
    return 0;
}
