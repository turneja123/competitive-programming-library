//https://leetcode.com/contest/biweekly-contest-139/problems/find-the-maximum-sequence-value-of-array/
int dp[405][128][405];
int dp_rev[405][128][405];
class Solution {
public:
    int maxValue(vector<int>& a, int k) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 128; j++) {
                for (int s = 0; s <= n; s++) {
                    dp[i][j][s] = 0;
                    dp_rev[i][j][s] = 0;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            dp[i][a[i]][1] = 1;
            if (i != 0) {
                for (int j = 0; j < 128; j++) {
                    for (int s = 1; s <= n; s++) {
                        dp[i][j][s] = max(dp[i][j][s], dp[i - 1][j][s]);
                        dp[i][a[i] | j][s] = max(dp[i][a[i] | j][s], dp[i - 1][j][s - 1]);
                    }
                }
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            dp_rev[i][a[i]][1] = 1;
            if (i != n - 1) {
                for (int j = 0; j < 128; j++) {
                    for (int s = 1; s <= n; s++) {
                        dp_rev[i][j][s] = max(dp_rev[i][j][s], dp_rev[i + 1][j][s]);
                        dp_rev[i][a[i] | j][s] = max(dp_rev[i][a[i] | j][s], dp_rev[i + 1][j][s - 1]);
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n - 1; i++) {
            for (int l = 0; l < 128; l++) {
                for (int r = 0; r < 128; r++) {
                    if (dp[i][l][k] == 1 && dp_rev[i + 1][r][k] == 1) {
                        ans = max(ans, l ^ r);
                    }
                }
            }
        }
        return ans;
    }
};
