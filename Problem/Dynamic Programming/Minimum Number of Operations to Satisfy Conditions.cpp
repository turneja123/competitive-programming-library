//https://leetcode.com/problems/minimum-number-of-operations-to-satisfy-conditions/
class Solution {
public:
    int INF = 1e9;
    int minimumOperations(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> freq(m, vector<int>(10, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                freq[j][grid[i][j]]++;
            }
        }
        vector<vector<int>> dp(m, vector<int>(10, INF));
        for (int i = 0; i < 10; i++) {
            dp[0][i] = n - freq[0][i];
        }
        for (int j = 1; j < m; j++) {
            for (int i = 0; i < 10; i++) {
                for (int k = 0; k < 10; k++) {
                    if (i == k) {
                        continue;
                    }
                    dp[j][i] = min(dp[j][i], n - freq[j][i] + dp[j - 1][k]);
                }
            }
        }
        int ans = INF;
        for (int i = 0; i < 10; i++) {
            ans = min(ans, dp[m - 1][i]);
        }
        return ans;
        
    }
};