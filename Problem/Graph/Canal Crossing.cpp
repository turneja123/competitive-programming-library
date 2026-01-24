//https://qoj.ac/problem/15631
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;


int deg[N];
vector<pair<int, int>> adj[N];

ll ans = 0;

void dfs(int u, int p) {
    for (auto [v, wt] : adj[u]) {
        if (v != p) {
            dfs(v, u);
            if (deg[v]) {
                ans += wt;
            }
            deg[u] ^= deg[v];
        }
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        deg[u]++, deg[v]++;
    }
    for (int i = 0; i < n; i++) {
        deg[i] %= 2;
    }
    dfs(0, 0);
    cout << ans;


    return 0;
}
