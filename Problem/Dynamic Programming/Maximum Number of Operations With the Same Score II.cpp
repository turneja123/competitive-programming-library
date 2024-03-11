//https://leetcode.com/contest/biweekly-contest-124/problems/maximum-number-of-operations-with-the-same-score-ii/
class Solution {
public:
    
    int f(vector<int> &nums, vector<vector<int>> &dp, int l, int r, int sum, int ans, int n) {
        if (r - l < 1 || l < 0 || r > n - 1 || dp[l][r] != 0) {
            return ans;
        }
        dp[l][r] = ans;
        
        if (l < r - 1 && nums[l] + nums[l + 1] == sum) {
            dp[l][r] = max(dp[l][r], f(nums, dp, l + 2, r, sum, ans + 1, n));
        }
        if (l != r && nums[l] + nums[r] == sum) {
            dp[l][r] = max(dp[l][r], f(nums, dp, l + 1, r - 1, sum, ans + 1, n));
        }
        if (r > l + 1 && nums[r] + nums[r - 1] == sum) {
            dp[l][r] = max(dp[l][r], f(nums, dp, l, r - 2, sum, ans + 1, n));
        }
        
        return dp[l][r];
        
    }
    
    
    int maxOperations(vector<int>& nums) {
        if (nums.size() == 2) {
            return 1;
        }
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        int ans = f(nums, dp, 2, n - 1, nums[0] + nums[1], 1, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = 0;
            }
        }
        ans = max(ans, f(nums, dp, 0, n - 3, nums[n - 1] + nums[n - 2], 1, n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = 0;
            }
        }
        ans = max(ans, f(nums, dp, 1, n - 2, nums[0] + nums[n - 1], 1, n));
        return ans;
        
    }
};