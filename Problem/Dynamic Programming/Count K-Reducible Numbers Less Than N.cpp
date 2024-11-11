//https://leetcode.com/contest/weekly-contest-423/problems/count-k-reducible-numbers-less-than-n/
const int N = 805;
const long long M = 1e9 + 7;
long long dp[N][N][3];
class Solution {
public:
    bool dfs(int n, int k) {
        if (k == 0) {
            return n == 1;
        }
        n = __builtin_popcount(n);
        return dfs(n, k - 1);
    }

    long long calc(string s, int k) {
        int n = s.size();
        if (s[0] == '1') {
            dp[0][1][2] = 1;
        } else {
            dp[0][1][1] = 1;
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= i + 1; j++) {
                if (s[i] == '1') {
                    dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j - 1][0]) % M;
                    dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j - 1][1]) % M;
                    dp[i][j][2] = (dp[i][j][2] + dp[i - 1][j - 1][2]) % M;

                    dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j][1]) % M;
                    dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][0] + dp[i - 1][j][2]) % M;
                } else {
                    dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j - 1][0]) % M;
                    dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j - 1][1] + dp[i - 1][j - 1][2]) % M;

                    dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][0]) % M;
                    dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j][1]) % M;
                    dp[i][j][2] = (dp[i][j][2] + dp[i - 1][j][2]) % M;

                }
            }
        }
        long long ans = 0;
        for (int j = 1; j <= n; j++) {
            bool can = dfs(j, k - 1);
            if (!can) {
                continue;
            }
            for (int i = 0; i < n; i++) {
                ans = (ans + dp[i][j][0]) % M;
                if (i != n - 1) {
                    ans = (ans + dp[i][j][1] + dp[i][j][2]) % M;
                }
            }
        }
        return ans;

    }

    int countKReducibleNumbers(string s, int k) {
        long long ans = calc(s, k);
        int n = s.size();
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j][0] = 0;
                dp[i][j][1] = 0;
                dp[i][j][2] = 0;
            }
        }
        return ans % M;
    }
};
