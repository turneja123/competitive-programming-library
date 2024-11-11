//https://atcoder.jp/contests/abc335/tasks/abc335_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

pair<int, int> a[N];
vector<int> adj[N];
vector<int> eq[N];

int dp[N];
bool vis[N];

int dfs(int u, vector<int> &comp) {
    comp.push_back(u);
    vis[u] = true;
    int mx = dp[u];
    for (int v : eq[u]) {
        if (!vis[v]) {
            mx = max(mx, dfs(v, comp));
        }
    }
    return mx;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (a[u].first > a[v].first) {
            adj[u].push_back(v);
        } else if (a[u].first < a[v].first) {
            adj[v].push_back(u);
        } else {
            eq[u].push_back(v);
            eq[v].push_back(u);
        }
    }
    sort(a, a + n);
    dp[0] = 1;
    int ans;
    for (int i = 0; i < n;) {
        int r = i;
        while (r < n && a[i].first == a[r].first) {
            int u = a[r].second;
            for (int v : adj[u]) {
                if (dp[v] != 0) {
                    dp[u] = max(dp[u], dp[v] + 1);
                }
            }
            r++;
        }
        while (i < r) {
            int u = a[i].second;
            if (!vis[u]) {
                vector<int> comp;
                int mx = dfs(u, comp);
                for (int v : comp) {
                    dp[v] = mx;
                }
            }
            if (u == n - 1) {
                ans = dp[u];
            }
            i++;
        }
    }
    cout << ans;
    return 0;
}
