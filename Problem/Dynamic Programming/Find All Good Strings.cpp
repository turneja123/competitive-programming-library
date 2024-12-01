//https://leetcode.com/contest/weekly-contest-182/problems/find-all-good-strings/
const int N = 505;
const long long M = 1e9 + 7;
class Solution {
public:
    int prefix[N];
    int trans[N][26];
    long long dp[N][N][3][3];

    void add(int i, int xn, int yn, int ck, int d, int jx, int jy) {
        if (ck > d) {
            dp[i][jx][xn][0] += dp[i - 1][jy][yn][0] + dp[i - 1][jy][yn][2];
            dp[i][jx][xn][1] += dp[i - 1][jy][yn][1];
        } else if (ck == d) {
            dp[i][jx][xn][0] += dp[i - 1][jy][yn][0];
            dp[i][jx][xn][1] += dp[i - 1][jy][yn][1];
            dp[i][jx][xn][2] += dp[i - 1][jy][yn][2];
        } else {
            dp[i][jx][xn][0] += dp[i - 1][jy][yn][0];
            dp[i][jx][xn][1] += dp[i - 1][jy][yn][1] + dp[i - 1][jy][yn][2];
        }
        dp[i][jx][xn][0] %= M, dp[i][jx][xn][1] %= M, dp[i][jx][xn][2] %= M;
        return;
    }

    long long calc(string n, string k, string s) {
        for (int d = 0; d < 26; d++) {
            int cn = n[0] - 'a', ck = k[0] - 'a';
            if (cn > d && ck > d) {
                dp[0][s[0] == ('a' + d)][0][0]++;
            } else if (cn > d && ck == d) {
                dp[0][s[0] == ('a' + d)][0][2]++;
            } else if (cn > d && ck < d) {
                dp[0][s[0] == ('a' + d)][0][1]++;
            } else if (cn == d && ck > d) {
                dp[0][s[0] == ('a' + d)][2][0]++;
            } else if (cn == d && ck == d) {
                dp[0][s[0] == ('a' + d)][2][2]++;
            } else if (cn == d && ck < d) {
                dp[0][s[0] == ('a' + d)][2][1]++;
            } else if (cn < d && ck > d) {
                dp[0][s[0] == ('a' + d)][1][0]++;
            } else if (cn < d && ck == d) {
                dp[0][s[0] == ('a' + d)][1][2]++;
            } else if (cn < d && ck < d) {
                dp[0][s[0] == ('a' + d)][1][1]++;
            }
        }

        for (int i = 1; i < n.size(); i++) {
            int cn  = n[i] - 'a', ck = k[i] - 'a';
            for (int j = 0; j < s.size(); j++) {
                for (int d = 0; d < 26; d++) {
                    if (cn > d) {
                        add(i, 0, 0, ck, d, trans[j][d], j);
                        add(i, 0, 2, ck, d, trans[j][d], j);
                        add(i, 1, 1, ck, d, trans[j][d], j);
                    } else if (cn == d) {
                        add(i, 0, 0, ck, d, trans[j][d], j);
                        add(i, 1, 1, ck, d, trans[j][d], j);
                        add(i, 2, 2, ck, d, trans[j][d], j);
                    } else {
                        add(i, 0, 0, ck, d, trans[j][d], j);
                        add(i, 1, 1, ck, d, trans[j][d], j);
                        add(i, 1, 2, ck, d, trans[j][d], j);
                    }
                }
            }
        }
        long long ans = 0;
        for (int j = 0; j < s.size(); j++) {
            ans = (ans + dp[n.size() - 1][j][2][0] + dp[n.size() - 1][j][2][2] + dp[n.size() - 1][j][1][2] + dp[n.size() - 1][j][1][0]) % M;
        }
        return ans;
    }

    int findGoodStrings(int n, string s1, string s2, string s) {
        int m = s.size();
        int k = 0;
        for (int i = 1; i < m; i++) {
            while (k > 0 && s[k] != s[i]) {
                k = prefix[k - 1];
            }
            if (s[k] == s[i]) {
                k++;
            }
            prefix[i] = k;
        }
        for (int i = 0; i <= m; i++) {
            for (int c = 0; c < 26; c++) {
                char ch = 'a' + c;
                if (i < m && ch == s[i]) {
                    trans[i][c] = i + 1;
                } else {
                    if (i == 0) {
                        trans[i][c] = 0;
                    } else {
                        trans[i][c] = trans[prefix[i - 1]][c];
                    }
                }
            }
        }
        return calc(s1, s2, s);
    }
};
