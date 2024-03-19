//https://cses.fi/problemset/task/1130/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
int dp[N][2];
int best[N];

void dfs(int u, int p) {
    if (adj[u].size() == 1 && adj[u][0] == p) {
        return;
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            dp[u][0] += best[v];
        }
    }
    int sum = dp[u][0];
    for (int v : adj[u]) {
        if (v != p) {
            dp[u][1] = max(dp[u][1], sum - best[v] + dp[v][0] + 1);
        }
    }
    best[u] = max(dp[u][0], dp[u][1]);
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    cout << best[0];

    return 0;
}
