//https://cses.fi/problemset/task/2078
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const ll M = 1e9 + 7;

vector<int> adj[N];
int vis[N];

void dfs(int u) {
    vis[u] = 1;
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}


int main() {
    IOS;
    int n, m, c = 0;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i);
            c++;
        }
    }
    ll ans = 1;
    for (int i = 0; i < m - n + c; i++) {
        ans = ans * 2 % M;
    }
    cout << ans;

    return 0;
}
