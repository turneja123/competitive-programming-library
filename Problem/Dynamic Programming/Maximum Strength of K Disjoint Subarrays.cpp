//https://leetcode.com/contest/weekly-contest-388/problems/maximum-strength-of-k-disjoint-subarrays/
class Solution {
public:
    long long maximumStrength(vector<int>& nums, int k) {
        long long INF = 1e18;
        int n = nums.size();
        vector<vector<long long>> dp(n, vector<long long>(k + 1, -INF));
        dp[0][0] = 0;
        dp[0][1] = nums[0] * (long long)k;
        for (int i = 1; i < nums.size(); i++) {
            for (long long j = 0; j <= k; j++) {
                if (j == 0) {
                    dp[i][j] = 0;
                    continue;
                }
                if (j % 2 == 1) {
                    dp[i][j] = max(dp[i - 1][j] + ((long long)k - j + 1) * nums[i], dp[i - 1][j - 1] + ((long long)k - j + 1) * nums[i]);
                } else {
                    dp[i][j] = max(dp[i - 1][j] - ((long long)k - j + 1) * nums[i], dp[i - 1][j - 1] - ((long long)k - j + 1) * nums[i]);
                }
            }
        }
        long long ans = -INF;
        for (int i = 0; i < nums.size(); i++) {
            ans = max(ans, dp[i][k]);
        }
        return ans;
    }
};