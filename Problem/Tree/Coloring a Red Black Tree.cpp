//https://codeforces.com/contest/2219/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = double;

const int N = 2e5 + 5;

int deg[N];
int vis[N];
vector<int> adj[N];

ld dp[N][2];


void dfs(int u, int p) {
    vis[u] = 1;
    ld s = 0;
    vector<ld> child;
    for (int v : adj[u]) {
        if (v != p && !vis[v]) {
            dfs(v, u);
            s += dp[v][0];
            child.push_back(dp[v][0] - dp[v][1]);
        }
    }
    sort(child.begin(), child.end());
    reverse(child.begin(), child.end());
    dp[u][0] = s + (ld)(adj[u].size()) / (deg[u] + 1);
    dp[u][1] = (!deg[u] ? 1e18 : s + (ld)(adj[u].size()) / deg[u]);
    for (int i = 0; i < child.size(); i++) {
        s -= child[i];
        dp[u][0] = min(dp[u][0], s + (ld)(adj[u].size()) / (deg[u] + 2 + i));
        dp[u][1] = min(dp[u][1], s + (ld)(adj[u].size()) / (deg[u] + 1 + i));
    }
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        for (int i = 0; i < n; i++) {
            vis[i] = s[i] - '0';
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            for (int j : adj[i]) {
                deg[i] += vis[j];
            }
        }
        ld ans = 0;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, i);
                ans += dp[i][1];
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            deg[i] = 0;
        }

    }
    return 0;
}
