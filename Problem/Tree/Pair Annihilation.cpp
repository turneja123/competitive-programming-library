//https://atcoder.jp/contests/abc409/tasks/abc409_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
long long ans[N];
vector<pair<int, int>> adj[N];

void dfs(int u, int p) {
    for (auto [v, wt] : adj[u]) {
        if (v != p) {
            dfs(v, u);
            ans[u] += ans[v] + (long long)wt * abs(a[v]);
            a[u] += a[v];
        }
    }
}


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    dfs(0, 0);
    cout << ans[0];
    return 0;
}
