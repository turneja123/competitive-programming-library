//https://codeforces.com/contest/2018/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int depth[N];
int far[N];
int leaf[N];
int diff[N];

vector<int> adj[N];

void dfs(int u, int p) {
    leaf[u] = 1;
    far[u] = -1;
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            far[u] = max(far[u], far[v]);
            leaf[u] = 0;

        }
    }
    if (leaf[u]) {
        far[u] = depth[u];
    }
    return;
}

int main() {
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
        for (int i = 0; i < n; i++) {
            diff[depth[i]]++;
            diff[far[i] + 1]--;
        }
        int ans = 0, cur = 0;
        for (int i = 0; i <= n; i++) {
            cur += diff[i];
            ans = max(cur, ans);
        }
        cout << n - ans << endl;
        for (int i = 0; i <= n; i++) {
            diff[i] = 0;
            adj[i].clear();
        }
    }
    return 0;
}
