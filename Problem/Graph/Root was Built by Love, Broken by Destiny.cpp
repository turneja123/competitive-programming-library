//https://codeforces.com/contest/2127/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 1e9 + 7;

vector<int> adj[N];
int deg[N];
int col[N];
ll fact[N];

void dfs(int u, int p, ll &ans) {
    for (int v : adj[u]) {
        if (col[v] == -1) {
            col[v] = col[u] ^ 1;
            dfs(v, u, ans);
        } else if (v != p) {
            ans = 0;
        }
    }
}

int main() {
    IOS;
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            deg[i] = 0;
            col[i] = -1;
            adj[i].clear();
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[u]++;
            deg[v]++;
        }
        if (n == 2) {
            cout << 2 << endl;
            continue;
        }
        ll ans = 2;
        col[0] = 0;
        dfs(0, 0, ans);
        int x = 0, y = 0;
        for (int u = 0; u < n; u++) {
            x += col[u] == 0, y += col[u] == 1;
            int ct = 0, ct2 = 0;
            for (int v : adj[u]) {
                if (col[u] == col[v]) {
                    ans = 0;
                }
                if (deg[v] == 1) {
                    ct++;
                } else {
                    ct2++;
                }
            }
            if (ct2 > 2) {
                ans = 0;
            }
            ans = ans * fact[ct] % M;
        }
        if (x > 1 && y > 1) {
            ans = ans * 2 % M;
        }
        cout << ans << endl;


    }
    return 0;
}
