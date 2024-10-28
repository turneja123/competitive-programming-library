//https://cses.fi/problemset/task/1132/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];

int depth[N];
int subtree[N];
int aux[N];
int child[N];
int dp[N];

void dfs_subtree(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs_subtree(v, u);
            if (subtree[v] + 1 > subtree[u]) {
                subtree[u] = subtree[v] + 1;
                child[u] = v;
            }
        }
    }
    for (int v : adj[u]) {
        if (v != p && v != child[u]) {
            aux[u] = max(aux[u], subtree[v] + 1);
        }
    }
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p && v != child[u]) {
            dp[v] = max(dp[u] + 1, subtree[u] + 1);
        } else if (v != p && v == child[u]) {
            dp[v] = max(dp[u] + 1, aux[u] + 1);
        }
        if (v != p) {
            dfs(v, u);
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
    dfs(0, 0);
    for (int i = 0; i < n; i++) {
        cout << max(subtree[i], dp[i]) << " ";
    }
    return 0;
}
