//https://leetcode.com/contest/weekly-contest-426/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/
class Solution {
public:

    void dfs(int u, int p, vector<vector<int>> &adj, vector<vector<int>> &subtree) {
        subtree[u][0] = 1;
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, adj, subtree);
                subtree[u][0] += subtree[v][1];
                subtree[u][1] += subtree[v][0];
            }
        }
        return;
    }

    void dfs_dp(int u, int p, vector<vector<int>> &adj, vector<vector<int>> &subtree, vector<vector<int>> &dp) {
        for (int v : adj[u]) {
            if (v != p) {
                dp[v][0] += dp[u][1] + (subtree[u][1] - subtree[v][0]);
                dp[v][1] += dp[u][0] + (subtree[u][0] - subtree[v][1]);
                dfs_dp(v, u, adj, subtree, dp);
            }
        }
        return;
    }

    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1, m = edges2.size() + 1;
        vector<vector<int>> adj1(n, vector<int>());
        vector<vector<int>> adj2(m, vector<int>());
        for (int i = 0; i < n - 1; i++) {
            int u = edges1[i][0], v = edges1[i][1];
            adj1[u].push_back(v);
            adj1[v].push_back(u);
        }
        for (int i = 0; i < m - 1; i++) {
            int u = edges2[i][0], v = edges2[i][1];
            adj2[u].push_back(v);
            adj2[v].push_back(u);
        }
        vector<vector<int>> subtree1(n, vector<int>(2, 0));
        vector<vector<int>> subtree2(m, vector<int>(2, 0));
        dfs(0, 0, adj1, subtree1);
        dfs(0, 0, adj2, subtree2);
        vector<vector<int>> dp1(n, vector<int>(2, 0));
        vector<vector<int>> dp2(m, vector<int>(2, 0));
        dfs_dp(0, 0, adj1, subtree1, dp1);
        dfs_dp(0, 0, adj2, subtree2, dp2);
        int mx = 0;
        for (int i = 0; i < m; i++) {
            mx = max(mx, subtree2[i][1] + dp2[i][1]);
        }
        vector<int> ans(n, 0);
        for (int i = 0; i < n; i++) {
            ans[i] = subtree1[i][0] + dp1[i][0] + mx;
        }
        return ans;
    }
};
