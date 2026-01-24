//https://qoj.ac/contest/2828/problem/16118
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 1e9 + 7;

vector<pair<int, int>> c[N], adj[N];
bool vis[N];
int fix[N];
int deg[N];
ll fact[N];

int ok = 1;

void dfs_init(int u) {
    vis[u] = 1;
    for (auto [v, c] : adj[u]) {
        if (fix[v] == -1) {
            fix[v] = c;
            dfs_init(v);
        } else if (fix[u] != c && fix[v] != c) {
            ok = 0;
        }
    }
}

int d = 0, s = 0;

void dfs(int u) {
    vis[u] = 1;
    d += adj[u].size();
    s++;
    for (auto [v, _] : adj[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}

int main() {
    IOS;
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % M;
    }
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        fix[i] = -1;
    }
    for (int i = 0; i < m; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        u--, v--, x--;
        c[x].push_back({u, v});
    }
    for (int i = 0; i < n; i++) {
        if (c[i].size() > 1) {
            int s = c[i].size();
            for (auto [u, v] : c[i]) {
                deg[u]++;
                deg[v]++;
            }
            int k = -1;
            for (auto [u, v] : c[i]) {
                if (deg[u] == s) {
                    k = u;
                }
                if (deg[v] == s) {
                    k = v;
                }
            }
            if (k == -1) {
                cout << 0;
                return 0;
            }
            fix[k] = i;
            for (auto [u, v] : c[i]) {
                deg[u]--;
                deg[v]--;
            }
        } else if (c[i].size() == 1) {
            auto [u, v] = c[i][0];
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
        }
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i] && fix[i] != -1) {
            dfs_init(i);
        }
    }
    if (!ok) {
        cout << 0;
        return 0;
    }
    ll ans = 1; int fr = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i);
            d /= 2;
            if (d == s - 1) {
                fr++;
                ans = ans * s % M;
            } else if (d == s) {
                ans = ans * 2 % M;
            } else if (d > s) {
                ans = 0;
            }
            s = 0, d = 0;
        }
    }
    cout << ans * fact[fr] % M;

    return 0;
}
