//https://dmoj.ca/problem/coci19c1p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const long long INF = 1e18;

vector<int> adj[N];
vector<long long> dp[N][3];

int a[N];
bool vis[N];

vector<long long> merge_subtrees(vector<long long> &a, vector<long long> &b) {
    int n = a.size(), m = b.size();
    vector<long long> c(n + m - 1, INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i + j] = min(c[i + j], a[i] + b[j]);
        }
    }
    return c;
}

void dfs(int u, int p) {
    dp[u][0] = {0};
    dp[u][1] = {a[u]};
    dp[u][2] = {INF};
    vis[u] = true;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            vector<long long> x = merge_subtrees(dp[u][0], dp[v][0]);
            vector<long long> y = merge_subtrees(dp[u][0], dp[v][1]);
            vector<long long> z = merge_subtrees(dp[u][0], dp[v][2]);
            int n = x.size(), m = y.size(), k = z.size();
            int S = max(max(n, m), k);
            dp[u][0].resize(S);
            for (int i = 0; i < S; i++) {
                dp[u][0][i] = INF;
                if (i < n) {
                    dp[u][0][i] = min(dp[u][0][i], x[i]);
                }
                if (i < m) {
                    dp[u][0][i] = min(dp[u][0][i], y[i]);
                }
                if (i < k) {
                    dp[u][0][i] = min(dp[u][0][i], z[i]);
                }
            }

            x = merge_subtrees(dp[u][1], dp[v][1]);
            y = merge_subtrees(dp[u][1], dp[v][2]);
            vector<long long> x1 = merge_subtrees(dp[u][2], dp[v][0]);
            vector<long long> y1 = merge_subtrees(dp[u][2], dp[v][1]);
            vector<long long> z1 = merge_subtrees(dp[u][2], dp[v][2]);
            n = x.size(), m = y.size(); int n1 = x1.size(), m1 = y1.size(), k1 = z1.size();
            S = max(n + 2, max(m + 1, max(n1, max(m1 + 1, k1))));
            dp[u][2].resize(S);
            for (int i = 0; i < S; i++) {
                dp[u][2][i] = INF;
            }
            for (int i = 0; i < S; i++) {
                if (i < n) {
                    dp[u][2][i + 2] = min(dp[u][2][i + 2], x[i]);
                }
                if (i < m) {
                    dp[u][2][i + 1] = min(dp[u][2][i + 1], y[i]);
                }
                if (i < n1) {
                    dp[u][2][i] = min(dp[u][2][i], x1[i]);
                }
                if (i < m1) {
                    dp[u][2][i + 1] = min(dp[u][2][i + 1], y1[i]);
                }
                if (i < k1) {
                    dp[u][2][i] = min(dp[u][2][i], z1[i]);
                }
            }

            dp[u][1] = merge_subtrees(dp[u][1], dp[v][0]);
        }
    }
    return;
}

int main() {
    IOS;
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<long long> ans{0};
    for (int u = 0; u < N; u++) {
        if (!vis[u]) {
            dfs(u, u);
            int n = dp[u][0].size(), m = dp[u][1].size(), k = dp[u][2].size();
            int S = max(n, max(m, k));
            vector<long long> cur(S, INF);
            for (int i = 0; i < S; i++) {
                if (i < n) {
                    cur[i] = min(cur[i], dp[u][0][i]);
                }
                if (i < m) {
                    cur[i] = min(cur[i], dp[u][1][i]);
                }
                if (i < k) {
                    cur[i] = min(cur[i], dp[u][2][i]);
                }
            }
            ans = merge_subtrees(ans, cur);
        }
    }
    for (int i = ans.size() - 2; i >= 0; i--) {
        ans[i] = min(ans[i], ans[i + 1]);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        long long s;
        cin >> s;
        int p = upper_bound(ans.begin(), ans.end(), s) - ans.begin();
        cout << p - 1 << endl;
    }


    return 0;
}
