//https://leetcode.com/problems/find-the-maximum-sum-of-node-values/
class Solution {
public:
    void dfs(int u, int p, vector<vector<int>> &adj, vector<int>& nums, int k, vector<vector<long long>> &dp) {
        if (adj[u].size() == 1 && adj[u][0] == p) {
            dp[u][0] = nums[u];
            return;
        }
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (v != p) {
                dfs(v, u, adj, nums, k, dp);
                if (dp[u][0] < 0) {
                    dp[u][0] = max(dp[u][0], dp[v][0] + nums[u]);
                    dp[u][0] = max(dp[u][0], dp[v][1] + nums[u]);
                    dp[u][1] = max(dp[u][1], dp[v][0] + (nums[v] ^ k) - nums[v] + (nums[u] ^ k));
                    dp[u][1] = max(dp[u][1], dp[v][1] - (nums[v] ^ k) + nums[v] + (nums[u] ^ k));
                } else {
                    long long max1 = dp[u][0];
                    max1 = max(max1, dp[u][0] + dp[v][0]);
                    max1 = max(max1, dp[u][0] + dp[v][1]);
                    max1 = max(max1, dp[u][1] + nums[u] - (nums[u] ^ k) + dp[v][1] + nums[v] - (nums[v] ^ k));
                    max1 = max(max1, dp[u][1] + nums[u] - (nums[u] ^ k) + dp[v][0] - nums[v] + (nums[v] ^ k));

                    long long max2 = dp[u][1];
                    max2 = max(max2, dp[u][1] + dp[v][0]);
                    max2 = max(max2, dp[u][1] + dp[v][1]);
                    max2 = max(max2, dp[u][0] - nums[u] + (nums[u] ^ k) + dp[v][1] + nums[v] - (nums[v] ^ k));
                    max2 = max(max2, dp[u][0] - nums[u] + (nums[u] ^ k) + dp[v][0] - nums[v] + (nums[v] ^ k));

                    dp[u][0] = max1;
                    dp[u][1] = max2;
                }
            }
        }
        return;
    }
    
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < edges.size(); i++) {
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        long long INF = -1e12;
        vector<vector<long long>> dp(n, vector<long long>(2, INF));
        dfs(0, -1, adj, nums, k, dp);
        return max(dp[0][0], dp[0][1]);
    }
};