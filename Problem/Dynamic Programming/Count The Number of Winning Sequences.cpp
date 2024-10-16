const long long M = 1e9 + 7;
long long dp[1005][2005][3];
class Solution {
public:
    int countWinningSequences(string s) {
        int mid = 1002;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            for (int j = mid - n; j <= mid + n; j++) {
                dp[i][j][0] = 0;
                dp[i][j][1] = 0;
                dp[i][j][2] = 0;
            }
        }
        if (s[0] == 'F') {
            dp[0][mid][0] = 1;
            dp[0][mid + 1][1] = 1;
            dp[0][mid - 1][2] = 1;
        } else if (s[0] == 'W') {
            dp[0][mid - 1][0] = 1;
            dp[0][mid][1] = 1;
            dp[0][mid + 1][2] = 1;

        } else if (s[0] == 'E') {
            dp[0][mid + 1][0] = 1;
            dp[0][mid - 1][1] = 1;
            dp[0][mid][2] = 1;
        }
        for (int i = 1; i < n; i++) {
            for (int j = mid - i; j <= mid + i; j++) {
                if (s[i] == 'F') {
                    dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][1] + dp[i - 1][j][2]) % M;
                    dp[i][j + 1][1] = (dp[i][j + 1][1] + dp[i - 1][j][0] + dp[i - 1][j][2]) % M;
                    dp[i][j - 1][2] = (dp[i][j - 1][2] + dp[i - 1][j][0] + dp[i - 1][j][1]) % M;
                } else if (s[i] == 'W') {
                    dp[i][j - 1][0] = (dp[i][j - 1][0] + dp[i - 1][j][1] + dp[i - 1][j][2]) % M;
                    dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j][0] + dp[i - 1][j][2]) % M;
                    dp[i][j + 1][2] = (dp[i][j + 1][2] + dp[i - 1][j][0] + dp[i - 1][j][1]) % M;

                } else if (s[i] == 'E') {
                    dp[i][j + 1][0] = (dp[i][j + 1][0] + dp[i - 1][j][1] + dp[i - 1][j][2]) % M;
                    dp[i][j - 1][1] = (dp[i][j - 1][1] + dp[i - 1][j][0] + dp[i - 1][j][2]) % M;
                    dp[i][j][2] = (dp[i][j][2] + dp[i - 1][j][0] + dp[i - 1][j][1]) % M;
                }
            }
        }
        long long ans = 0;
        for (int j = mid + 1; j <= mid + n; j++) {
            ans += dp[n - 1][j][0] + dp[n - 1][j][1] + dp[n - 1][j][2];
        }
        return ans % M;
    }
};
