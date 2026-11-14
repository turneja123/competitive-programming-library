//https://codeforces.com/contest/2271/problem/H1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

vector<int> adj[N];
int parent[N];
int sz[N];
int h[N];
int dp[N][N][2];

void dfs(int u, int p) {
    parent[u] = p;
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int calc(int l, int r, int s, int flag, int n) {
    if (l == r) {
        return h[l] % 2 == n % 2;
    }
    if (dp[l][r][s] != -1) {
        return dp[l][r][s];
    }
    int a = calc(l + 1, r, s ^ (h[l] % 2), flag ^ 1, n);
    int b = calc(l, r - 1, s ^ (h[r] % 2), flag ^ 1, n);
    int ans = ((flag == 1) ? max(a, b) : min(a, b));
    if (s == 1) {
        int c = calc(l, r, 0, flag ^ 1, n);
        if (flag) {
            ans = max(ans, c);
        } else {
            ans = min(ans, c);
        }
    }
    return dp[l][r][s] = ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, x, y;
        cin >> n >> x >> y;
        x--, y--;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(x, x);
        vector<int> path;
        int v = y;
        while (v != x) {
            path.push_back(v);
            v = parent[v];
        }
        path.push_back(x);
        reverse(path.begin(), path.end());
        int d = path.size() - 1;
        if (d == 1) {
            cout << n % 2 << endl;
        } else {
            for (int i = 0; i < d; i++) {
                h[i] = sz[path[i]] - sz[path[i + 1]] - 1;
            }
            h[d] = sz[y] - 1;
            for (int l = 1; l < d; l++) {
                for (int r = l; r < d; r++) {
                    dp[l][r][0] = -1, dp[l][r][1] = -1;
                }
            }
            cout << calc(1, d - 1, (h[0] + h[d]) % 2, 1, n) << endl;
        }
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }

    return 0;
}
