//https://leetcode.com/contest/biweekly-contest-124/problems/maximize-consecutive-elements-in-an-array-after-modification/
class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][0] = 1;
        dp[0][1] = 1;
        int ans = 1;
        for (int i = 1; i < n; i++) {
            if (i > 1 && nums[i] == nums[i - 1] && nums[i] == nums[i - 2]) {
                dp[i][0] = dp[i - 1][0];
                dp[i][1] = dp[i - 1][1];
                continue;
            }
            dp[i][0] = 1;
            dp[i][1] = 1;
            if (nums[i] - nums[i - 1] == 1) {
                dp[i][0] = max(dp[i][0], dp[i - 1][0] + 1);
                dp[i][1] = max(dp[i][1], dp[i - 1][1] + 1);
            }
            if (nums[i] - nums[i - 1] == 2) {
                dp[i][0] = max(dp[i][0], dp[i - 1][1] + 1);
            }
            if (nums[i] - nums[i - 1] == 0) {
                dp[i][0] = dp[i - 1][0];
                dp[i][1] = dp[i - 1][1];
                
                dp[i][1] = max(dp[i][1], dp[i - 1][0] + 1);
            }
            ans = max(ans, dp[i][0]);
            ans = max(ans, dp[i][1]);
        }
        return ans;
  
    }
};