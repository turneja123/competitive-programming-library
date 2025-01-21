//https://atcoder.jp/contests/abc160/tasks/abc160_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

vector<int> adj[N];

long long inv[N];
long long fact[N];
long long factinv[N];

int sz[N];
long long subtree[N];
long long dp[N];
long long ans[N];

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    subtree[u] = fact[sz[u] - 1];
    for (int v : adj[u]) {
        if (v != p) {
            subtree[u] = subtree[u] * subtree[v] % M * factinv[sz[v]] % M;
        }
    }
    return;
}

void dfs(int u, int p, int n) {
    for (int v : adj[u]) {
        if (v != p) {
            long long aux = subtree[u] * modPow(subtree[v], M - 2) % M * factinv[sz[u] - 1] % M * fact[sz[v]] % M * fact[sz[u] - 1 - sz[v]] % M;
            dp[v] = dp[u] * aux % M * fact[n - sz[v] - 1] % M * factinv[sz[u] - 1 - sz[v]] % M * factinv[n - sz[u]] % M;
            ans[v] = fact[n - 1] * factinv[sz[v] - 1] % M * factinv[n - sz[v]] % M * subtree[v] % M * dp[v] % M;
            dfs(v, u, n);
        }
    }

}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }

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
    dp[0] = 1;
    ans[0] = subtree[0];
    dfs(0, 0, n);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
