//https://leetcode.com/problems/count-the-number-of-powerful-integers/
class Solution {
public:
    long long dp[20][2];
    long long calc(long long a, int limit, string s) {
        long long k = 0, temp = a; int j = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            int c = s[i] - '0';
            if (c < a % 10) {
                dp[j][0] = 1;
                dp[j][1] = 0;
            } else if (c > a % 10) {
                dp[j][0] = 0;
                dp[j][1] = 1;
            } else {
                if (i == (int)(s.size() - 1) || dp[j - 1][0] == 1) {
                    dp[j][0] = 1;
                    dp[j][1] = 0;
                } else {
                    dp[j][0] = 0;
                    dp[j][1] = 1;
                }
            }
            a /= 10;
            j++;
        }
        if (stoll(s) > temp) {
            return 0;
        }
        long long ans = 1;
        for (int i = s.size(); a > 0; i++) {
            dp[i][0] = 0;
            dp[i][1] = 0;
            for (int c = 0; c <= limit; c++) {
                if (c < a % 10) {
                    dp[i][0] += dp[i - 1][0] + dp[i - 1][1];
                    if (c != 0) {
                        ans += dp[i - 1][0] + dp[i - 1][1];
                    }
                } else if (c > a % 10) {
                    dp[i][1] += dp[i - 1][0] + dp[i - 1][1];
                    if (a > 9) {
                        ans += dp[i - 1][0] + dp[i - 1][1];
                    }
                } else {
                    dp[i][0] += dp[i - 1][0];
                    dp[i][1] += dp[i - 1][1];
                    if (c != 0) {
                        ans += dp[i - 1][0];
                        if (a > 9) {
                            ans += dp[i - 1][1];
                             cout << ans << endl;
                        }
                    }
                }
            }
            a /= 10;
        }
        return ans;
    }


    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        return calc(finish, limit, s) - calc(start - 1, limit, s);
    }
};