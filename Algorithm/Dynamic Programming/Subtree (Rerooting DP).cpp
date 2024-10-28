//https://atcoder.jp/contests/dp/tasks/dp_v
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
long long M;

vector<int> adj[N];
vector<int> child[N];

long long subtree[N];
long long dp[N];

void dfs_subtree(int u, int p) {
    subtree[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_subtree(v, u);
            child[u].push_back(v);
            subtree[u] = subtree[u] * (subtree[v] + 1) % M;
        }
    }
    return;
}

void dfs(int u, int p) {
    if (u == p) {
        dp[u] = 1;
    }
    if (child[u].empty()) {
        return;
    }
    int m = child[u].size();
    vector<long long> pref_prod(m), suf_prod(m);
    for (int i = 0; i < m; i++) {
        pref_prod[i] = ((i == 0) ? subtree[child[u][i]] + 1 : pref_prod[i - 1] * (subtree[child[u][i]] + 1) % M);
    }
    for (int i = m - 1; i >= 0; i--) {
        suf_prod[i] = ((i == m - 1) ? subtree[child[u][i]] + 1 : suf_prod[i + 1] * (subtree[child[u][i]] + 1) % M);
    }
    for (int i = 0; i < child[u].size(); i++) {
        int v = child[u][i];
        dp[v] = dp[u] * ((i == 0) ? 1 : pref_prod[i - 1]) % M * ((i == m - 1) ? 1 : suf_prod[i + 1]) % M + 1;
        dfs(v, u);
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n >> M;
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
        cout << subtree[i] * dp[i] % M << endl;
    }
    return 0;
}
