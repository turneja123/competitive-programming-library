//https://atcoder.jp/contests/abc207/tasks/abc207_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const long long M = 1e9 + 7;

vector<int> adj[N];
vector<long long> dp[N][3];

vector<long long> merge_subtrees(vector<long long> &a, vector<long long> &b) {
    int n = a.size(), m = b.size();
    vector<long long> c(n + m - 1, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i + j] = (c[i + j] + a[i] * b[j]) % M;
        }
    }
    return c;
}

void dfs(int u, int p) {
    dp[u][0] = {1};
    dp[u][1] = {0};
    dp[u][2] = {0, 1};
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            vector<long long> x, y, z, r;
            int n, m, k, e, S;
            x = merge_subtrees(dp[u][0], dp[v][2]);
            y = merge_subtrees(dp[u][1], dp[v][0]);
            z = merge_subtrees(dp[u][1], dp[v][1]);
            r = merge_subtrees(dp[u][1], dp[v][2]);
            n = x.size(), m = y.size(), k = z.size(), e = r.size();
            S = max(n + 1, max(m, max(k, e)));
            dp[u][1].resize(S);
            for (int i = 0; i < S; i++) {
                dp[u][1][i] = 0;
            }
            for (int i = 0; i < S; i++) {
                if (i < n) {
                    dp[u][1][i + 1] = (dp[u][1][i + 1] + x[i]) % M;
                }
                if (i < m) {
                    dp[u][1][i] = (dp[u][1][i] + y[i]) % M;
                }
                if (i < k) {
                    dp[u][1][i] = (dp[u][1][i] + z[i]) % M;
                }
                if (i < e) {
                    dp[u][1][i] = (dp[u][1][i] + r[i]) % M;
                }
            }

            x = merge_subtrees(dp[u][2], dp[v][0]);
            y = merge_subtrees(dp[u][2], dp[v][1]);
            z = merge_subtrees(dp[u][2], dp[v][2]);
            n = x.size(), m = y.size(), k = z.size();
            S = max(n + 1, max(m, k));
            dp[u][2].resize(S);
            for (int i = 0; i < S; i++) {
                dp[u][2][i] = 0;
            }
            for (int i = 0; i < S; i++) {
                if (i < n) {
                    dp[u][2][i + 1] = (dp[u][2][i + 1] + x[i]) % M;
                }
                if (i < m) {
                    dp[u][2][i] = (dp[u][2][i] + y[i]) % M;
                }
                if (i < k) {
                    dp[u][2][i] = (dp[u][2][i] + z[i]) % M;
                }
            }

            x = merge_subtrees(dp[u][0], dp[v][0]);
            y = merge_subtrees(dp[u][0], dp[v][1]);
            n = x.size(), m = y.size();
            S = max(n, m);
            dp[u][0].resize(S);
            for (int i = 0; i < S; i++) {
                dp[u][0][i] = 0;
            }
            for (int i = 0; i < S; i++) {
                if (i < n) {
                    dp[u][0][i] = (dp[u][0][i] + x[i]) % M;
                }
                if (i < m) {
                    dp[u][0][i] = (dp[u][0][i] + y[i]) % M;
                }
            }

        }
    }
    return;
}


int main() {
    IOS;
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
    for (int i = 0; i <= n; i++) {
        long long cur = 0;
        if (dp[0][0].size() > i) {
            cur += dp[0][0][i];
        }
        if (dp[0][1].size() > i) {
            cur += dp[0][1][i];
        }
        if (dp[0][2].size() > i) {
            cur += dp[0][2][i];
        }
        cout << cur % M << endl;
    }

    return 0;
}
