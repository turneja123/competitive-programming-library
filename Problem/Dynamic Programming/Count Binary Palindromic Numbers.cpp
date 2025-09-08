//https://leetcode.com/problems/count-binary-palindromic-numbers/description/
long long dp[60][3][3];
class Solution {
public:
    void add(int i, int xn, int yn, int ck, int d) {
        if (ck > d) {
            dp[i][xn][0] += dp[i - 1][yn][0] + dp[i - 1][yn][2] + dp[i - 1][yn][1];
        } else if (ck == d) {
            dp[i][xn][0] += dp[i - 1][yn][0];
            dp[i][xn][1] += dp[i - 1][yn][1];
            dp[i][xn][2] += dp[i - 1][yn][2];
        } else {
            dp[i][xn][1] += dp[i - 1][yn][1] + dp[i - 1][yn][2] + dp[i - 1][yn][0];
        }
        return;
    }

    long long calc(__int128 n) {
        if (n < 2) {
            return n + 1;
        }
        vector<int> v;
        while (n > 0) {
            v.push_back(n % 2);
            n /= 2;
        }
        reverse(v.begin(), v.end());
        int m = v.size();
        for (int dx = 0; dx < 3; dx++) {
            for (int dy = 0; dy < 3; dy++) {
                dp[0][dx][dy] = 0;
            }
        }
        for (int d = 1; d < 2; d++) {
            int cn = v[0], ck = v[m - 1];
            if (cn > d && ck > d) {
                dp[0][0][0] += 1;
            } else if (cn > d && ck == d) {
                dp[0][0][2] += 1;
            } else if (cn > d && ck < d) {
                dp[0][0][1] += 1;
            } else if (cn == d && ck > d) {
                dp[0][2][0] += 1;
            } else if (cn == d && ck == d) {
                dp[0][2][2] += 1;
            } else if (cn == d && ck < d) {
                dp[0][2][1] += 1;
            } else if (cn < d && ck > d) {
                dp[0][1][0] += 1;
            } else if (cn < d && ck == d) {
                dp[0][1][2] += 1;
            } else if (cn < d && ck < d) {
                dp[0][1][1] += 1;
            }
        }
        for (int i = 1; i < m / 2 + m % 2; i++) {
            for (int dx = 0; dx < 3; dx++) {
                for (int dy = 0; dy < 3; dy++) {
                    dp[i][dx][dy] = 0;
                }
            }
            int cn = v[i], ck = v[m - 1 - i];
            for (int d = 0; d < 2; d++) {
                if (cn > d) {
                    add(i, 0, 0, ck, d);
                    add(i, 0, 2, ck, d);
                    add(i, 1, 1, ck, d);
                } else if (cn == d) {
                    add(i, 0, 0, ck, d);
                    add(i, 1, 1, ck, d);
                    add(i, 2, 2, ck, d);
                } else {
                    add(i, 0, 0, ck, d);
                    add(i, 1, 1, ck, d);
                    add(i, 1, 2, ck, d);
                }
            }
        }
        long long ans = 2;
        for (int i = 0; i < m / 2; i++) {
            if (2 * (i + 1) == m) {
                ans += dp[i][0][0] + dp[i][0][1] + dp[i][0][2] + dp[i][2][0] + dp[i][2][2];
            } else {
                ans += dp[i][0][0] + dp[i][0][1] + dp[i][0][2] + dp[i][1][0] + dp[i][1][1] + dp[i][1][2] + dp[i][2][0] + dp[i][2][1] + dp[i][2][2];
                if (2 * (i + 1) + 1 < m) {
                    ans += (dp[i][0][0] + dp[i][0][1] + dp[i][0][2] + dp[i][1][0] + dp[i][1][1] + dp[i][1][2] + dp[i][2][0] + dp[i][2][1] + dp[i][2][2]) * 2;
                }
            }
        }
        if (m % 2 == 1) {
            ans += dp[m / 2 + m % 2 - 1][0][0] + dp[m / 2 + m % 2 - 1][0][1] + dp[m / 2 + m % 2 - 1][0][2] + dp[m / 2 + m % 2 - 1][2][0] + dp[m / 2 + m % 2 - 1][2][2];
        }
        return ans;
    }


    int countBinaryPalindromes(long long n) {
        return calc(n);
    }
};
