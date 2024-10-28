//https://leetcode.com/contest/weekly-contest-421/problems/find-the-number-of-subsequences-with-equal-gcd/
const int N = 205;
const long long M = 1e9 + 7;
long long dp[N][N][N];

class Solution {
public:
    int subsequencePairCount(vector<int>& a) {
        int n = a.size(), m = 0;
        for (int i = 0; i < n; i++) {
            m = max(m, a[i]);
        }
        dp[0][a[0]][0] = 1;
        dp[0][0][a[0]] = 1;
        for (int i = 1; i < n; i++) {
            for (int l = 0; l <= m; l++) {
                for (int r = 0; r <= m; r++) {
                    if (l == 0 && r == 0) {
                        dp[i][a[i]][0] = 1;
                        dp[i][0][a[i]] = 1;
                        continue;
                    }
                    if (l == 0) {
                        dp[i][a[i]][r] = (dp[i][a[i]][r] + dp[i - 1][0][r]) % M;
                        dp[i][0][__gcd(r, a[i])] = (dp[i][0][__gcd(r, a[i])]+ dp[i - 1][0][r]) % M;
                    } else if (r == 0) {
                        dp[i][__gcd(l, a[i])][0] = (dp[i][__gcd(l, a[i])][0] + dp[i - 1][l][0]) % M;
                        dp[i][l][a[i]] = (dp[i][l][a[i]] + dp[i - 1][l][0]) % M;
                    } else {
                        dp[i][__gcd(l, a[i])][r] = (dp[i][__gcd(l, a[i])][r] + dp[i - 1][l][r]) % M;
                        dp[i][l][__gcd(r, a[i])] = (dp[i][l][__gcd(r, a[i])]+ dp[i - 1][l][r]) % M;
                    }
                    dp[i][l][r] = (dp[i][l][r] + dp[i - 1][l][r]) % M;
                }
            }
        }
        long long sum = 0;
        for (int j = 1; j <= m; j++) {
            sum += dp[n - 1][j][j];
        }
        for (int i = 0; i < n; i++) {
            for (int l = 0; l <= m; l++) {
                for (int r = 0; r <= m; r++) {
                    dp[i][l][r] = 0;
                }
            }
        }
        return sum % M;

    }
};
