//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description/
class Solution {
public:
    const int INF = 1e9;
    int dp[1005][105][2];
    int maxProfit(int k, vector<int>& a) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= k; j++) {
                dp[i][j][0] = -INF;
                dp[i][j][1] = -INF;
            }
        }
        dp[0][0][0] = 0, dp[0][1][1] = -a[0];
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= k; j++) {
                if (dp[i - 1][j][1] != -INF) {
                    dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + a[i]);
                }
                if (dp[i - 1][j - 1][0] != -INF) {
                    dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - a[i]);
                }
            }
        }
        int ans = 0;
        for (int i = 0; i <= k; i++) {
            ans = max(ans, dp[n - 1][i][0]);
        }
        return ans;
    }
};
