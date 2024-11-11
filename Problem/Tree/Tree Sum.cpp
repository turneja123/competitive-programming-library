//https://www.spoj.com/problems/TREESUM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e4 + 5;
const int K = 21;
const long long M = 1e9 + 7;

vector<int> adj[N];

int sz[N];
long long nck[K][K];
long long dp[K][N];
long long subtree[K][N];

void dfs_subtree(int u, int p, int k) {
    sz[u] = 1;
    for (int i = 1; i <= k; i++) {
        subtree[i][u] = 1;
    }

    for (int v : adj[u]) {
        if (v != p) {
            dfs_subtree(v, u, k);
            sz[u] += sz[v];
            for (int i = 1; i <= k; i++) {
                for (int j = i; j > 0; j--) {
                    subtree[i][u] += subtree[j][v] * nck[i][i - j] % M;
                }
                subtree[i][u] = (subtree[i][u] + sz[v]) % M;
            }
        }
    }
    return;
}

void dfs(int u, int p, int k, int n) {
    for (int v : adj[u]) {
        if (v != p) {
            for (int i = 1; i <= k; i++) {
                long long pw = 1;
                for (int j = i; j > 0; j--) {
                    dp[i][v] = (dp[i][v] + dp[j][u] * nck[i][i - j] % M + subtree[j][u] * nck[i][i - j] % M - subtree[j][v] * nck[i][i - j] % M * pw % M + M) % M;
                    pw = pw * 2 % M;
                }
                dp[i][v] = (dp[i][v] + n - sz[v] * pw % M + M) % M;
            }
            dfs(v, u, k, n);
        }
    }
}

int main() {
    IOS;
    nck[0][0] = 1;
    for (int n = 1; n < K; n++) {
        nck[n][0] = nck[n][n] = 1;
        for (int k = 1; k < n; k++) {
            nck[n][k] = (nck[n - 1][k - 1] + nck[n - 1][k]) % M;
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs_subtree(0, 0, k);
        dfs(0, 0, k, n);
        for (int i = 0; i < n; i++) {
            cout << (subtree[k][i] + dp[k][i]) % M << endl;
            adj[i].clear();
            sz[i] = 0;
            for (int j = 1; j <= k; j++) {
                dp[j][i] = 0;
                subtree[j][i] = 0;
            }
        }
        cout << endl;
    }

    return 0;
}

