//https://leetcode.com/problems/burst-balloons/
class Solution {
public:
    int dp[305][305];

    int maxCoins(vector<int>& a) {
        int ans = 0, n = a.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j + i < n; j++) {
                if (i == 0) {
                    dp[j][j] = ((j - 1 >= 0) ? a[j - 1] : 1) * a[j] * ((j + 1 < n) ? a[j + 1] : 1);
                    continue;
                }
                dp[j][j + i] = 0;
                for (int k = j; k <= j + i; k++) {
                    dp[j][j + i] = max(dp[j][j + i], ((j == k) ? 0 : dp[j][k - 1]) + dp[k + 1][j + i] +
                    ((j - 1 >= 0) ? a[j - 1] : 1) * a[k] * ((j + i + 1 < n) ? a[j + i + 1] : 1));
                }
            }
        }
        return dp[0][n - 1];

    }
};
