//https://atcoder.jp/contests/agc079/tasks/agc079_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const ll M = 998244353;

ll inv[N];
ll fact[N];
ll factinv[N];
ll dp[N];

int sz[N];
vector<int> adj[N];

void dfs(int u) {
    sz[u] = 1;
    for (int v : adj[u]) {
        dfs(v);
        sz[u] += sz[v];
    }
    dp[u] = fact[sz[u] - 1];
    for (int v : adj[u]) {
        dp[u] = dp[u] * factinv[sz[v]] % M * dp[v] % M;
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

    int t;
    cin >> t;
    while (t--) {

        int n;
        cin >> n;
        set<int> st;
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            p--;
            auto it = st.upper_bound(p);
            while (it != st.end() && *it < i) {
                adj[i].push_back(*it);
                it = st.erase(it);
            }

            st.insert(i);
        }
        for (int x : st) {
            adj[n].push_back(x);
        }
        dfs(n);
        cout << dp[n] << endl;
        for (int i = 0; i <= n; i++) {
            adj[i].clear();
        }
    }

    return 0;
}
