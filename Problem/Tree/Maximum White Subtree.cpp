//https://codeforces.com/contest/1324/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];

int a[N];;
long long subtree[N];
long long dp[N];

void dfs_subtree(int u, int p) {
    subtree[u] = ((a[u] == 1) ? 1 : -1);
    for (int v : adj[u]) {
        if (v != p) {
            dfs_subtree(v, u);
            subtree[u] += max(0ll, subtree[v]);
        }
    }
    return;
}

void dfs(int u, int p, int n) {
    for (int v : adj[u]) {
        if (v != p) {
            dp[v] = max(0ll, dp[u] + subtree[u] - max(0ll, subtree[v]));
            dfs(v, u, n);
        }
    }
    return;
}

int main() {
    IOS;
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
        cout << subtree[i] + dp[i] << " ";
    }
    return 0;
}
