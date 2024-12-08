//https://codeforces.com/contest/2050/problem/G
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
int subtree[N];
int dp[N];

void dfs_subtree(int u, int p) {
    sz[u] = 0;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_subtree(v, u);
            sz[u]++;
            subtree[u] = max(subtree[u], subtree[v]);
        }
    }
    if (sz[u] == 0) {
        subtree[u] = 0;
    } else {
        subtree[u] = max(sz[u], subtree[u] + sz[u] - 1);
    }
    return;
}

void dfs(int u, int p) {
    multiset<int> st;
    for (int v : adj[u]) {
        if (v != p) {
            st.insert(subtree[v]);
        }
    }
    for (int v : adj[u]) {
        if (v != p) {
            st.erase(st.find(subtree[v]));
            dp[v] = max(dp[v], dp[u] + sz[u] - 1);
            if (st.size()) {
                dp[v] = max(dp[v], *st.rbegin() + sz[u] - 2 + (u != 0));
            }
            st.insert(subtree[v]);
            dfs(v, u);
        }
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
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
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max({ans, subtree[i] + (i != 0), dp[i] + sz[i]});
            sz[i] = 0, subtree[i] = 0, dp[i] = 0;
            adj[i].clear();
        }
        cout << ans << endl;
    }
    return 0;
}
