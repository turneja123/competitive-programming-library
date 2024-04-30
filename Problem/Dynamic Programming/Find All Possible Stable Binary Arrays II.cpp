//https://leetcode.com/problems/find-all-possible-stable-binary-arrays-ii/description/
class Solution {
public:
    long long M = 1e9 + 7;
    long long dp[2005][2005][2];
    
    int numberOfStableArrays(int zero, int one, int limit) {
        long long ans = 0;
        int n = zero + one;
        dp[0][0][0] = 1, dp[0][1][1] = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j][0] = (dp[i - 1][j][0] + dp[i - 1][j][1]) % M;
                if (i - limit - 1 >= 0) {
                    dp[i][j][0] = (dp[i][j][0] - dp[i - limit - 1][j][1] + M) % M;
                }
                if (i == limit && j == 0) {
                    dp[i][j][0] = 0;
                }
                if (j != 0) {
                    dp[i][j][1] = (dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1]) % M;
                    if (i - limit - 1 >= 0 && j - limit - 1 >= 0) {
                        dp[i][j][1] = (dp[i][j][1] - dp[i - limit - 1][j - limit - 1][0] + M) % M;
                    }
                }
                if (i == limit && j == limit + 1) {
                    dp[i][j][1] = 0;
                }
            }
        }
        return (dp[n - 1][one][0] + dp[n - 1][one][1]) % M;
        
    }
};