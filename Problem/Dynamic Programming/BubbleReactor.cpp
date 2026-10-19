//https://codeforces.com/contest/1218/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 15005;
const int INF = 1e9;

vector<int> adj[N];
vector<int> cyc;
int on_cyc[N];
int up[N];
int depth[N];
int vis[N];

void dfs(int u, int p) {
    up[u] = p;
    vis[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !vis[v]) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        } else if (v != p && vis[v] && depth[u] - depth[v] > 1) {
            int x = u;
            cyc.push_back(x);
            while (1) {
                x = up[x];
                cyc.push_back(x);
                if (x == v) {
                    break;
                }
            }
        }
    }
}

int sz[N];
ll dp_cyc[N][2];

void dfs_cyc(int u, int p, int n) {
    sz[u] = 1;
    ll s = 0;
    int best = -INF, who = -1;
    for (int v : adj[u]) {
        if (v != p && !on_cyc[v]) {
            dfs_cyc(v, u, n);
            sz[u] += sz[v];
            s += dp_cyc[v][0];
            if (dp_cyc[v][1] - dp_cyc[v][0] + n - sz[v] > best) {
                best = dp_cyc[v][1] - dp_cyc[v][0] + n - sz[v];
                who = v;
            }
        }
    }
    dp_cyc[u][0] = sz[u] + s;
    dp_cyc[u][1] = n + s;
    if (who != -1) {
        dp_cyc[u][1] = max(dp_cyc[u][1], best + s);
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    for (int u : cyc) {
        on_cyc[u] = 1;
    }
    for (int u : cyc) {
        dfs_cyc(u, u, n);
    }
    int m = cyc.size();
    vector<ll> dp(m), dp_nx(m);
    vector<int> pref(m);

    for (int i = 0; i < m; i++) {
        int u = cyc[i];
        dp[i] = dp_cyc[u][1];
        pref[i] = (i == 0 ? 0 : pref[i - 1]) + sz[u];
    }

    auto calc_pref = [&](int l, int r) -> int {
        if (r >= l) {
            return pref[r] - (l == 0 ? 0 : pref[l - 1]);
        }
        return pref[r] + pref[m - 1] - pref[l - 1];
    };

    for (int i = 0; i < m - 1; i++) {
        for (int l = 0; l < m; l++) {
            int r = l + i;
            if (r >= m) {
                r -= m;
            }

            int add = r + 1;
            if (add >= m) {
                add -= m;
            }
            int u = cyc[add];

            dp_nx[l] = max(dp_nx[l], dp[l] + dp_cyc[u][0] + n - calc_pref(l, add));

            add = l - 1;
            if (add < 0) {
                add = m - 1;
            }
            u = cyc[add];

            dp_nx[add] = max(dp_nx[add], dp[l] + dp_cyc[u][0] + n - calc_pref(add, r));

        }
        for (int j = 0; j < m; j++) {
            dp[j] = dp_nx[j];
            dp_nx[j] = 0;
        }

    }
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << " ";


    return 0;
}
