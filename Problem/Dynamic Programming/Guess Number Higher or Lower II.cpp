//https://leetcode.com/problems/guess-number-higher-or-lower-ii/description
class Solution {
public:
    int dp[205][205];

    int calc(int l, int r) {
        if (l > r) {
            return 0;
        }
        if (l == r) {
            return 0;
        }
        if (dp[l][r] != 1e9) {
            return dp[l][r];
        }
        int ans = 1e9;
        for (int i = l; i <= r; i++) {
            ans = min(ans, i + max(calc(l, i - 1), calc(i + 1, r)));
        }
        return dp[l][r] = ans;
    }

    int getMoneyAmount(int n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = 1e9;
            }
        }
        for (int i = 1; i <= n; i++) {
            dp[1][n] = min(dp[1][n], i + max(calc(1, i - 1), calc(i + 1, n)));
        }
        if (n == 1) {
            return 0;
        }
        return dp[1][n];
    }
};
