//https://codeforces.com/contest/1187/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];

int sz[N];
long long subtree[N];
long long dp[N];

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
            subtree[u] += subtree[v];
        }
    }
    subtree[u] += sz[u];

}

void dfs(int u, int p, int n) {
    long long sum = 0;
    for (int v : adj[u]) {
        if (v != p) {
            sum += subtree[v];
        }
    }
    for (int v : adj[u]) {
        if (v != p) {
            dp[v] = dp[u] + (sum - subtree[v]) + n - sz[v];
            dfs(v, u, n);
        }
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
    dfs_subtree(0, 0);
    dfs(0, 0, n);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, subtree[i] + dp[i] + n - sz[i]);
    }
    cout << ans;
    return 0;
}
