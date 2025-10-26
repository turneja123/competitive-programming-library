//https://www.codechef.com/problems/WATSUP
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 18;

int a[N];
int p[N];

vector<int> adj[N];

int dp[N][2];
int val[N];
int tin[N];
int tout[N];
int up[K][N];
int timer = 0;

void dfs(int u, int p) {
    tin[u] = timer++;
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    for (int v : adj[u]) {
        if (v != p) {
            val[v] = val[u] - val[u] / a[v];
            dfs(v, u);
        }
    }
    tout[u] = timer++;
}

bool dfs_chk(int u, int p, int k, int need) {
    if (k < need) {
        return false;
    }
    bool can = true;
    for (int v : adj[u]) {
        if (v != p) {
            can &= dfs_chk(v, u, k - k / a[v], need);
        }
    }
    return can;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int k = K - 1; k >= 0; k--) {
        if (!is_ancestor(up[k][u], v)) {
            u = up[k][u];
        }
    }
    return up[0][u];
}



int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i < n; i++) {
            cin >> p[i];
            p[i]--;
            adj[p[i]].push_back(i);
            adj[i].push_back(p[i]);
        }
        for (int i = 1; i < n; i++) {
            cin >> a[i];
        }
        val[0] = k;
        dfs(0, 0);
        int l = 0, r = k, ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            int u = -1;
            for (int i = 0; i < n; i++) {
                if (val[i] < mid) {
                    u = (u == -1 ? i : lca(u, i));
                }
            }
            if (u == -1) {
                ans = mid;
                l = mid + 1;
                continue;
            }
            vector<int> v;
            while (u != 0) {
                v.push_back(u);
                u = p[u];
            }
            v.push_back(0);
            reverse(v.begin(), v.end());
            int m = v.size();
            dp[0][0] = k, dp[0][1] = k;
            for (int i = 1; i < m; i++) {
                dp[i][0] = dp[i - 1][0] - dp[i - 1][0] / a[v[i]];
                dp[i][1] = max(dp[i - 1][1] - dp[i - 1][1] / a[v[i]], dp[i - 1][0]);
            }
            if (dfs_chk(v.back(), p[v.back()], dp[m - 1][1], mid)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }

        }
        cout << ans << endl;
        timer = 0;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }

    return 0;
}
