//https://codeforces.com/contest/815/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const int INF = 1e9 + 1;

vector<int> adj[N];
vector<int> dp[N][2];

int c[N], d[N];

vector<int> merge_subtrees(vector<int> &a, vector<int> &b) {
    int n = a.size(), m = b.size();
    vector<int> c(n + m - 1, INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i + j] = min(c[i + j], a[i] + b[j]);
        }
    }
    return c;
}

void dfs(int u, int p) {
    dp[u][0] = {0, c[u]};
    dp[u][1] = {INF, c[u] - d[u]};
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            dp[u][0] = merge_subtrees(dp[u][0], dp[v][0]);
            vector<int> x = merge_subtrees(dp[u][1], dp[v][1]);
            vector<int> y = merge_subtrees(dp[u][1], dp[v][0]);
            dp[u][1].resize(x.size());
            for (int i = 0; i < dp[u][1].size(); i++) {
                dp[u][1][i] = min(x[i], y[i]);
            }
        }
    }
    return;
}

int main() {
    IOS;
    int n, x;
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> c[i] >> d[i];
        if (i != 0) {
            int p;
            cin >> p;
            p--;
            adj[i].push_back(p);
            adj[p].push_back(i);
        }
    }
    dfs(0, 0);
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        if (dp[0][0][i] <= x || dp[0][1][i] <= x) {
            ans = i;
        }
    }
    cout << ans;

    return 0;
}
