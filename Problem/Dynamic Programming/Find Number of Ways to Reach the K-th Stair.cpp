//https://leetcode.com/problems/find-number-of-ways-to-reach-the-k-th-stair/description/
class Solution {
public:
    long long dp[64][32][2];
    int waysToReachStair(int k) {
        int ans = 0;
        dp[1][0][0] = 1; // 0 - up, 1 - down
        dp[1][1][1] = 1;
        if (k <= 2) {
            ans++;
        }
        for (int i = 2; i < 64; i++) {
            for (int j = 0; j < 32; j++) {
                dp[i][j][0] = dp[i - 1][j][0] + dp[i - 1][j][1];
                if (j != 0) {
                    dp[i][j][1] = dp[i - 1][j - 1][0];
                }
                int up = i - j;
                if (up > 29 || up + 1 < j) {
                    continue;
                }
                int n = (1 << up) - j;
                if (n == k) {
                    ans += dp[i][j][0] + dp[i][j][1];
                }
            }

        }
        return ans;
    }
};