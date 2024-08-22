//https://leetcode.com/contest/weekly-contest-348/problems/count-of-integers/
class Solution {
public:
    const long long M = 1e9 + 7;
    long long dp[25][250][3];

    long long calc(string s, int l, int r) {
        for (int i = 0; i < s.size(); i++) {
            for (int j = 0; j <= min(230, r); j++) {
                dp[i][j][0] = 0;
                dp[i][j][1] = 0;
                dp[i][j][2] = 0;
            }
        }
        for (int d = 1; d < 10; d++) {
            int c = s[0] - '0';
            if (c > d) {
                dp[0][d][0] = 1;
            } else if (c == d) {
                dp[0][d][2] = 1;
            } else {
                dp[0][d][1] = 1;
            }
        }
        for (int i = 1; i < s.size(); i++) {
            for (int j = 0; j <= min(230, r); j++) {
                for (int d = 0; d < 10; d++) {
                    if (d > j) {
                        continue;
                    }
                    int c = s[i] - '0';
                    if (c > d) {
                        dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j - d][0] + dp[i - 1][j - d][2]) % M;
                        dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j - d][1]) % M;
                    } else if (c == d) {
                        dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j - d][0]) % M;
                        dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j - d][1]) % M;
                        dp[i][j][2] = (dp[i][j][2] + dp[i - 1][j - d][2]) % M;
                    } else {
                        dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j - d][1] + dp[i - 1][j - d][2]) % M;
                        dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j - d][0]) % M;
                    }
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < s.size(); i++) {
            for (int j = l; j <= min(249, r); j++) {
                ans = (ans + dp[i][j][0] + dp[i][j][2]) % M;
                if (i != s.size() - 1) {
                    ans = (ans + dp[i][j][1]) % M;
                }
            }
        }
        return ans;
    }

    int check(string a, int l, int r) {
        int ct = 0;
        for (int i = 0; i < a.size(); i++) {
            ct += a[i] - '0';
        }
        if (ct >= l && ct <= r) {
            return 1;
        }
        return 0;
    }

    int count(string a, string b, int l, int r) {
        return (calc(b, l, r) - calc(a, l, r) + check(a, l, r) + M) %M;
    }
};
