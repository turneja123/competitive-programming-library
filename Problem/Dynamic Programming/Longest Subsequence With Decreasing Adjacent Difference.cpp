//https://leetcode.com/problems/longest-subsequence-with-decreasing-adjacent-difference/description/
class Solution {
public:
    int dp[301][301];
    int suf[301][301];

    int longestSubsequence(vector<int>& a) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            dp[a[i]][300] = 1;
            if (suf[a[i]][0] != 0) {
                dp[a[i]][0] = suf[a[i]][0] + 1;
            }

            for (int j = 1; j < 300; j++) {
                if (a[i] - j > 0) {
                    dp[a[i]][j] = max(dp[a[i]][j], suf[a[i] - j][j] + 1);
                }
                if (a[i] + j <= 300) {
                    dp[a[i]][j] = max(dp[a[i]][j], suf[a[i] + j][j] + 1);
                }
            }
            for (int j = 300; j >= 0; j--) {
                suf[a[i]][j] = (j == 300 ? dp[a[i]][300] : max(dp[a[i]][j], suf[a[i]][j + 1]));
            }
        }
        int ans = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 300; j++) {
                ans = max(ans, dp[a[i]][j]);
            }
        }
        return ans;
    }
};
