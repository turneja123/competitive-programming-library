//https://leetcode.com/problems/count-stepping-numbers-in-range/
class Solution {
public:
    const long long M = 1e9 + 7;
    long long dp[105][10][2];

    long long calc(string s) {
        int n = s.size();
        for (int i = 0; i < 10; i++) {
            dp[n - 1][i][0] = 0;
            dp[n - 1][i][1] = 0;
        }
        long long ans = 0;
        for (int i = 0; i <= 9; i++) {
            int c = s[n - 1] - '0';
            if (i <= c) {
                dp[n - 1][i][0]++;
                if (i != 0) {
                    ans++;
                }
            } else {
                dp[n - 1][i][1]++;
                if (s.size() > 1) {
                    ans++;
                }
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            int c = s[i] - '0';
            for (int cif = 0; cif <= 9; cif++) {
                dp[i][cif][0] = 0;
                dp[i][cif][1] = 0;
                for (int j = 0; j <= 9; j++) {
                    if (abs(cif - j) != 1) {
                        continue;
                    }  
                    if (cif < c) {
                        dp[i][cif][0] = (dp[i][cif][0] + dp[i + 1][j][0]) % M;
                        dp[i][cif][0] = (dp[i][cif][0] + dp[i + 1][j][1]) % M;
                        if (cif > 0) {
                            ans = (ans + dp[i + 1][j][0]) % M;
                            ans = (ans + dp[i + 1][j][1]) % M;
                        }
                    } else if (cif > c) {
                        dp[i][cif][1] = (dp[i][cif][1] + dp[i + 1][j][0]) % M;
                        dp[i][cif][1] = (dp[i][cif][1] + dp[i + 1][j][1]) % M;
                        if (i > 0 && cif > 0) {
                            ans = (ans + dp[i + 1][j][0]) % M;
                            ans = (ans + dp[i + 1][j][1]) % M;
                        }
                    } else {
                        dp[i][cif][0] = (dp[i][cif][0] + dp[i + 1][j][0]) % M;
                        dp[i][cif][1] = (dp[i][cif][1] + dp[i + 1][j][1]) % M;
                        if (cif > 0) {
                            ans = (ans + dp[i + 1][j][0]) % M;
                            if (i > 0) {
                                ans = (ans + dp[i + 1][j][1]) % M;
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }
    int check (string s) {
        for (int i = 1; i < s.size(); i++) {
            int r = s[i] - '0', l = s[i - 1] - '0';
            if (abs(r - l) != 1 ) {
                return 0;
            }
        }
        return 1;
    }
    
    int countSteppingNumbers(string low, string high) {
        return (calc(high) - calc(low) + check(low) + M) % M;
    }
};