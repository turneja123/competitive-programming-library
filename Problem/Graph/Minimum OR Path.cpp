//https://atcoder.jp/contests/abc408/tasks/abc408_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<pair<int, int>> adj[N];

bool vis[N];

void dfs(int u, int mask) {
    vis[u] = true;
    for (auto [v, wt] : adj[u]) {
        if (!vis[v]) {
            int c = mask & wt;
            if (c == 0) {
                dfs(v, mask);
            }
        }
    }
    return;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
    }
    int mask = 0;
    for (int j = 29; j >= 0; j--) {
        for (int i = 0; i < n; i++) {
            vis[i] = false;
        }
        vis[0] = true;
        mask ^= 1 << j;
        dfs(0, mask);
        if (!vis[n - 1]) {
            mask ^= 1 << j;
        }
    }
    int ans = ((1 << 30) - 1) ^ mask;
    cout << ans;
    return 0;
}
