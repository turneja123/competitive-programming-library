//https://www.codechef.com/problems/WLKLIM2?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;

ll dp[N][2];
vector<int> st;
vector<int> adj[N];
int ok[N];
int sz[N];
int go[N];

void dfs_subtree(int u, int p) {
    st.push_back(u);
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
            ok[u] |= ok[v];
            if (ok[v]) {
                go[u] = v;
            }
        }
    }
    st.pop_back();
}

void dfs(int u, int p, int n) {
    if (u == 0) {
        dp[u][0] = 1;
        dp[u][1] = sz[u] - 1 - sz[go[u]];
    } else if (u == n - 1) {
        dp[u][0] = (dp[p][0] + dp[p][1]) % M;
        dp[u][1] = 0;
        return;
    } else {
        dp[u][0] = (dp[p][0] + dp[p][1]) % M;
        dp[u][1] = ((dp[p][0] + dp[p][1]) * (sz[u] - 1 - sz[go[u]]) + dp[p][0]) % M;
    }
    dfs(go[u], u, n);
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
        ok[n - 1] = 1;
        dfs_subtree(0, -1);
        dfs(0, -1, n);
        cout << dp[n - 1][0] << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            ok[i] = 0;
            dp[i][0] = 0, dp[i][1] = 0;
        }

    }

    return 0;
}
