//https://usaco.org/index.php?page=viewproblem2&cpid=766
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 1e9 + 7;

vector<int> adj[N];
long long dp[N][4];
int a[N];
int best[N];

void dfs(int u, int p) {
    if (adj[u].size() == 1 && adj[u][0] == p) {
        if (a[u] == 0) {
            dp[u][1] = 1;
            dp[u][2] = 1;
            dp[u][3] = 1;
        } else {
            dp[u][a[u]] = 1;
        }
        return;
    }

    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            for (int c = 1; c <= 3; c++) {
                if (a[u] != 0 && c != a[u]) {
                    continue;
                }
                long long sum = 0;
                for (int j = 1; j <= 3; j++) {
                    if (c != j && dp[v][j] != -1) {
                        sum = (sum + dp[v][j]) % M;
                    }
                }
                if (dp[u][c] == -1) {
                    dp[u][c] = sum;
                } else {
                    dp[u][c] = (dp[u][c] * sum) % M;
                }
            }
        }
    }
    return;
}

int main() {
    //IOS;
    freopen("barnpainting.in", "r", stdin);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < k; i++) {
        int u, c;
        cin >> u >> c;
        a[--u] = c;
    }
    for (int i = 0; i < n; i++) {
        for (int c = 1; c <= 3; c++) {
            dp[i][c] = -1;
        }
    }
    dfs(0, 0);
    freopen("barnpainting.out", "w", stdout);
    if (a[0] == 0) {
        cout << (dp[0][1] + dp[0][2] + dp[0][3]) % M;
    } else {
        cout << dp[0][a[0]];
    }

    return 0;
}
