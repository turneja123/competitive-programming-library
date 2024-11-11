//https://codeforces.com/contest/2014/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
long long dp[N][2];
vector<int> adj[N];

void dfs(int u, int p, int c) {
    dp[u][0] = 0, dp[u][1] = a[u];
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, c);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += max(dp[v][0], dp[v][1] - 2 * c);
        }
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, c;
        cin >> n >> c;
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
        dfs(0, 0, c);
        cout << max(dp[0][0], dp[0][1]) << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }
    return 0;
}
