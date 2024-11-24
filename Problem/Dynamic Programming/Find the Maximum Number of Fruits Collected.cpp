//https://leetcode.com/contest/biweekly-contest-144/problems/find-the-maximum-number-of-fruits-collected/
const int N = 1005;
int dp[N][N];
class Solution {
public:
    int maxCollectedFruits(vector<vector<int>>& a) {
        int ans = 0, n = a.size();
        for (int i = 0; i < n; i++) {
            ans += a[i][i];
            for (int j = 0; j < n; j++) {
                dp[i][j] = -1;
            }
        }
        dp[0][n - 1] = a[0][n - 1];
        for (int i = 1; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (dp[i - 1][j] != -1) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j] + a[i][j]);
                }
                if (dp[i - 1][j - 1] != -1) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + a[i][j]);
                }
                if (j < n - 1 && dp[i - 1][j + 1] != -1) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j + 1] + a[i][j]);
                }
            }
        }
        dp[n - 1][0] = a[n - 1][0];
        for (int j = 1; j < n - 1; j++) {
            for (int i = j + 1; i < n; i++) {
                if (dp[i][j - 1] != -1) {
                    dp[i][j] = max(dp[i][j], dp[i][j - 1] + a[i][j]);
                }
                if (dp[i - 1][j - 1] != -1) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + a[i][j]);
                }
                if (i < n - 1 && dp[i + 1][j - 1] != -1) {
                    dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + a[i][j]);
                }
            }
        }
        return ans + dp[n - 2][n - 1] + dp[n - 1][n - 2];
    }
};
