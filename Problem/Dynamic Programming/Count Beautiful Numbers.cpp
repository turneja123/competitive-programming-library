//https://leetcode.com/contest/weekly-contest-441/problems/count-beautiful-numbers/
const int N = 9;
const int E = 9 * N + 5;
int dp[N][E][E][E][3];
class Solution {
public:
    int calc(int n) {
        if (n == 0) {
            return 0;
        }
        vector<int> b;
        while (n > 0) {
            b.push_back(n % 10);
            n /= 10;
        }

        reverse(b.begin(), b.end());
        for (int m = 1; m < E; m++) {
            for (int d = 1; d < 10; d++) {
                if (d < b[0]) {
                    dp[0][m][d % m][d][0]++;
                } else if (d == b[0]) {
                    dp[0][m][d % m][d][2]++;
                } else {
                    dp[0][m][d % m][d][1]++;
                }
            }
        }
        n = b.size();
        for (int i = 1; i < n; i++) {
            for (int m = 1; m < E; m++) {
                for (int j = 0; j < m; j++) {
                    for (int s = 1; s <= 9 * i; s++) {
                        for (int d = 0; d < 10; d++) {
                            if (d < b[i]) {
                                dp[i][m][(j * d) % m][s + d][0] += dp[i - 1][m][j][s][0] + dp[i - 1][m][j][s][2];
                                dp[i][m][(j * d) % m][s + d][1] += dp[i - 1][m][j][s][1];

                            } else if (d == b[i]) {
                                dp[i][m][(j * d) % m][s + d][0] += dp[i - 1][m][j][s][0];
                                dp[i][m][(j * d) % m][s + d][1] += dp[i - 1][m][j][s][1];
                                dp[i][m][(j * d) % m][s + d][2] += dp[i - 1][m][j][s][2];
                            } else {
                                dp[i][m][(j * d) % m][s + d][0] += dp[i - 1][m][j][s][0];
                                dp[i][m][(j * d) % m][s + d][1] += dp[i - 1][m][j][s][1] + dp[i - 1][m][j][s][2];
                            }
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int m = 0; m < E; m++) {
                for (int j = 0; j < m; j++) {
                    for (int s = 0; s <= 9 * (i + 1); s++) {
                        if (s == m && j == 0) {
                            ans += dp[i][m][j][s][0] + dp[i][m][j][s][2];
                            if (i != n - 1) {
                                ans += dp[i][m][j][s][1];
                            }
                        }
                        dp[i][m][j][s][0] = 0;
                        dp[i][m][j][s][1] = 0;
                        dp[i][m][j][s][2] = 0;
                    }
                }
            }
        }
        return ans;
    }

    int beautifulNumbers(int l, int r) {
        return calc(r) - calc(l - 1);
    }
};
