//https://leetcode.com/problems/count-the-number-of-inversions/
class Solution {
public:
    long long M = 1e9 + 7;
    long long dp[500][500];
    int x[500];

    int numberOfPermutations(int n, vector<vector<int>>& a) {
        for (int i = 1; i <= n; i++) {
            x[i] = -1;
        }
        int mx = 0;
        for (int i = 0; i < a.size(); i++) {
            int j = a[i][0] + 1, k = a[i][1];
            if (x[j] != -1 && k != x[j]) {
                return 0;
            }
            x[j] = k;
            mx = max(mx, k);
        }
        if (mx > x[n]) {
            return 0;
        }
        mx = x[n];

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= mx; j++) {
                dp[i][j] = -1;
            }
        }
        if (x[1] != -1) {
            if (x[1] != 0) {
                return 0;
            }
        }
        dp[1][0] = 1;

        int mn = 0;
        for (int i = 2; i <= n; i++) {
            if (x[i] == -1 || x[i] == 0) {
                dp[i][0] = 1;
            }
            for (int j = 1; j <= mx; j++) {
                for (int p = j; p >= mn && j - p < i; p--) {
                    if (dp[i - 1][p] != -1) {
                        if (dp[i][j] == -1) {
                            dp[i][j] = dp[i - 1][p];
                        } else {
                            dp[i][j] = (dp[i][j] + dp[i - 1][p]) % M;
                        }
                    }

                }
                if (x[i] != -1) {
                    if (x[i] != j) {
                        dp[i][j] = -1;
                    }
                }
            }
            mn = max(mn, x[i]);
        }
        long long ans = dp[n][x[n]];
        if (ans == -1) {
            return 0;
        }
        return ans;
    }
};
