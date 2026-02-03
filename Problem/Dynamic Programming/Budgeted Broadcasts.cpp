//https://ocpc2026w.eolymp.space/en/compete/g6s5o5k4n93719vrc5sak0hi3k/problem/2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 998244353;

vector<int> adj[N];
ll sub[N][3];
ll aux[N][3];
ll dp[N][3];

ll ans = 0;

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

void dfs_subtree(int u, int p) {
    sub[u][0] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_subtree(v, u);
            sub[u][0] = (sub[u][0] + sub[v][0] * (M + 1) / 2) % M;
            sub[u][1] = (sub[u][1] + (sub[v][0] + sub[v][1]) * (M + 1) / 2) % M;
            sub[u][2] = (sub[u][2] + (sub[v][0] + 2 * sub[v][1] + sub[v][2]) * (M + 1) / 2) % M;
        }
    }
}

void dfs(int u, int p, int n) {
    ans = (ans + (sub[u][1] + dp[u][1]) * (n + 3) - sub[u][2] - dp[u][2] + M + M) % M;
    for (int v : adj[u]) {
        if (v != p) {
            aux[v][0] = (sub[u][0] + dp[u][0] - sub[v][0] * (M + 1) / 2 % M + M) % M;
            aux[v][1] = (sub[u][1] + dp[u][1] - (sub[v][0] + sub[v][1]) * (M + 1) / 2 % M + M) % M;
            aux[v][2] = (sub[u][2] + dp[u][2] - (sub[v][0] + 2 * sub[v][1] + sub[v][2]) * (M + 1) / 2 % M + M) % M;

            dp[v][0] = (dp[v][0] + aux[v][0] * (M + 1) / 2) % M;
            dp[v][1] = (dp[v][1] + (aux[v][0] + aux[v][1]) * (M + 1) / 2) % M;
            dp[v][2] = (dp[v][2] + (aux[v][0] + 2 * aux[v][1] + aux[v][2]) * (M + 1) / 2) % M;

            dfs(v, u, n);
        }
    }
}

int main() {
    IOS;
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
    dfs(0, 0, n);
    cout << (n == 2 ? (M + 1) / 2 : modPow(2, n - 3)) * ans % M;

    return 0;
}
