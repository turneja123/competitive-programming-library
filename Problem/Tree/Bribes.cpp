//https://codeforces.com/contest/575/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 18;
const ll M = 1e9 + 7;

vector<pair<int, int>> adj[N];
int tin[N];
int tout[N];
int up[K][N];
int timer = 0;

int mul[N];
int add[N][2];

void dfs(int u, int p) {
    tin[u] = timer++;
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    for (auto [v, wt] : adj[u]) {
        if (v != p) {
            if (wt == 1) { //ide dole
                mul[v] = 0;
            } else if (wt == -1) {
                mul[v] = 1;
            } else {
                mul[v] = -1;
            }
            dfs(v, u);
        }
    }
    tout[u] = timer++;
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

ll modPow(ll a, ll y) {
    ll res = 1;
    while (y > 0) {
        if (y % 2 != 0) {
            res = res * a % M;
        }
        y /= 2;
        a = a * a % M;
    }
    return res;
}

void dfs_add(int u, int p, ll &ans) {
    for (auto [v, wt] : adj[u]) {
        if (v != p) {
            dfs_add(v, u, ans);
            add[u][0] += add[v][0];
            add[u][1] += add[v][1];
        }
    }
    if (mul[u] != -1) {
        ans += modPow(2, add[u][mul[u]]) - 1;
    }

}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, -w});
    }
    dfs(0, 0);
    int q;
    cin >> q;
    int u = 0;
    for (int i = 0; i < q; i++) {
        int v;
        cin >> v;
        v--;
        if (u == v) {
            continue;
        }
        int l = lca(u, v);
        if (u != l) {
            add[u][0]++;
            add[l][0]--;
        }
        if (v != l) {
            add[v][1]++;
            add[l][1]--;
        }
        u = v;
    }
    ll ans = 0;
    dfs_add(0, 0, ans);
    cout << ans % M;

    return 0;
}
