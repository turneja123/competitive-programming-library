//https://codeforces.com/contest/715/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
int m;

vector<pair<int, int>> adj[N];
int seen_c[N];
int sz[N];


ll ans = 0;

ll extendedEuclidean(ll a, ll b, ll *x, ll *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    ll x1, y1;
    ll gcd = extendedEuclidean(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

ll modInverse(ll b, ll m) {
    ll x, y;
    ll g = extendedEuclidean(b, m, &x, &y);
    if (g != 1) {
        return -1;
    }
    return (x % m + m) % m;
}

void dfs_sz(int u, int p) {
    sz[u] = 1;
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_sz(v, u);
            sz[u] += sz[v];
        }
    }
}

int dfs_cen(int u, int p, int n) {
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v] && 2 * sz[v] > n) {
            return dfs_cen(v, u, n);
        }
    }
    return u;
}

map<int, int> mp;

void dfs_add(int u, int p, int x, int pw) {
    mp[x]++;
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_add(v, u, ((ll)x + (ll)pw * wt) % m, (ll)pw * 10 % m);
        }
    }
}

void dfs_calc(int u, int p, int x, int pw) {
    int y = (m - x) % m * modInverse(pw, m) % m;
    auto it = mp.find(y);
    if (it != mp.end()) {
        ans += it->second;
    }
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_calc(v, u, ((ll)x * 10 + wt) % m, ((ll)pw * 10) % m);
        }
    }
    return;
}

void build(int u) {
    dfs_sz(u, u);
    int c = dfs_cen(u, u, sz[u]);
    mp[0]++;
    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            dfs_calc(v, c, wt % m, 10 % m);
            dfs_add(v, c, wt % m, 10 % m);
        }
    }
    ans += mp[0] - 1;
    mp.clear();
    reverse(adj[c].begin(), adj[c].end());
    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            dfs_calc(v, c, wt % m, 10 % m);
            dfs_add(v, c, wt % m, 10 % m);
        }
    }
    mp.clear();
    seen_c[c] = 1;
    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            build(v);
        }
    }

}

int main() {
    IOS;
    int n;
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    build(0);
    cout << ans;

    return 0;
}
