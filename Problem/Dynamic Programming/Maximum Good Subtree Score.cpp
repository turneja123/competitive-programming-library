//https://leetcode.com/problems/maximum-good-subtree-score/description/
const int N = 555;
const long long M = 1e9 + 7;
long long dp[N][2 * N];
long long dp_nx[2 * N];
class Solution {
public:
    vector<int> adj[N];
    int a[N];
    int mask[N];
    long long best[N];

    void dfs(int u, int p) {
        for (int j = 0; j < 1 << 10; j++) {
            dp[u][j] = 0;
        }
        dp[u][mask[u]] = a[u];
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
                for (int j = 0; j < 1 << 10; j++) {
                    if (j != 0 && dp[u][j] == 0) {
                        continue;
                    }
                    int complement = ((1 << 10) - 1) ^ j;
                    for (int s = complement; ; s = (s - 1) & complement) {
                        if (!(s != 0 && dp[v][s] == 0)) {
                            dp_nx[j | s] = max(dp_nx[j | s], dp[u][j] + dp[v][s]);
                        }
                        if (s == 0) {
                            break;
                        }
                    }
                }
                for (int j = 0; j < 1 << 10; j++) {
                    dp[u][j] = max(dp[u][j], dp_nx[j]);
                    dp_nx[j] = 0;
                }
            }
        }
        for (int j = 0; j < 1 << 10; j++) {
            best[u] = max(best[u], dp[u][j]);
        }
    }

    int goodSubtreeSum(vector<int>& vals, vector<int>& par) {
        int n = vals.size();
        for (int i = 0; i < n; i++) {
            a[i] = vals[i];
            while (vals[i] > 0) {
                int d = vals[i] % 10;
                int c = mask[i] & (1 << d);
                if (c != 0) {
                    a[i] = 0;
                }
                mask[i] |= 1 << d;
                vals[i] /= 10;
            }
        }
        for (int i = 1; i < n; i++) {
            adj[i].push_back(par[i]);
            adj[par[i]].push_back(i);
        }
        dfs(0, 0);
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans += best[i];
        }
        return ans % M;
    }
};
