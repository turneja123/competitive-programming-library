//https://codeforces.com/contest/2178/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;

ll inv[N];
ll fact[N];
ll factinv[N];

vector<int> adj[N];
vector<int> a;
int sz[N];
int sz_e[N];

void dfs(int u, int p) {
    sz[u] = 1;
    sz_e[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
            if (sz[v] % 2 == 0) {
                a.push_back(sz_e[v]);
            } else {
                sz_e[u] += sz_e[v];
            }
        }
    }
}

int main() {
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
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
        dfs(0, 0);
        int m = a.size();
        if (m == 0) {
            cout << 1 << endl;
        } else {
            ll ans = 1, s = 0;
            for (int i = 0; i < m; i++) {
                ans = ans * a[i] % M * a[i] % M;
                s = (s + inv[a[i]]) % M;
            }
            ans = ans * s % M * sz_e[0] % M * fact[m - 1] % M;
            cout << ans << endl;
        }
        a.clear();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }
    return 0;
}
