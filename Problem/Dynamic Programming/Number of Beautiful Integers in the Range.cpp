//https://leetcode.com/contest/biweekly-contest-111/problems/number-of-beautiful-integers-in-the-range/
class Solution {
public:
    long long dp[12][25][12][3];


    long long calc(int n, int k) {
        if (n == 0) {
            return 0;
        }
        vector<int> a;
        while (n > 0) {
            a.push_back(n % 10);
            n /= 10;
        }
        reverse(a.begin(), a.end());
        n = a.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                for (int ct = 0; ct <= n; ct++) {
                    dp[i][j][ct][0] = 0;
                    dp[i][j][ct][1] = 0;
                    dp[i][j][ct][2] = 0;
                }
            }
        }
        for (int d = 1; d < 10; d++) {
            if (a[0] > d) {
                dp[0][d % k][d % 2 == 0][0]++;
            } else if (a[0] == d) {
                dp[0][d % k][d % 2 == 0][2]++;
            } else {
                dp[0][d % k][d % 2 == 0][1]++;
            }
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < k; j++) {
                for (int ct = 0; ct <= n; ct++) {
                    for (int d = 0; d < 10; d++) {
                        if (a[i] > d) {
                            dp[i][(j * 10 + d) % k][ct + (d % 2 == 0)][0] += dp[i - 1][j][ct][0] + dp[i - 1][j][ct][2];
                            dp[i][(j * 10 + d) % k][ct + (d % 2 == 0)][1] += dp[i - 1][j][ct][1];
                        } else if (a[i] == d) {
                            dp[i][(j * 10 + d) % k][ct + (d % 2 == 0)][0] += dp[i - 1][j][ct][0];
                            dp[i][(j * 10 + d) % k][ct + (d % 2 == 0)][1] += dp[i - 1][j][ct][1];
                            dp[i][(j * 10 + d) % k][ct + (d % 2 == 0)][2] += dp[i - 1][j][ct][2];
                        } else {
                            dp[i][(j * 10 + d) % k][ct + (d % 2 == 0)][1] += dp[i - 1][j][ct][1] + dp[i - 1][j][ct][2];
                            dp[i][(j * 10 + d) % k][ct + (d % 2 == 0)][0] += dp[i - 1][j][ct][0];
                        }
                    }
                }
            }
        }
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                continue;
            }
            ans += dp[i][0][(i + 1) / 2][0] + dp[i][0][(i + 1) / 2][2];
            if (i != n - 1) {
                ans += dp[i][0][(i + 1) / 2][1];
            }
        }
        return ans;

    }

    int numberOfBeautifulIntegers(int low, int high, int k) {
        return calc(high, k) - calc(low - 1, k);
    }
};
