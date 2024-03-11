//https://leetcode.com/problems/apply-operations-to-make-two-strings-equal/description/
class Solution {
public:
    const static int N = 505;
    int dp[N][N][2]; //pozicija, broj jedinica, da li je trenutna pozicija 0 ili 1. resenje je dp[n-1][0][0]
    
    int minOperations(string s1, string s2, int x) {
        int n = s1.size(), INF = 1e9;
        vector<int> a(n, 0);
        for (int i = 0; i < n; i++) {
            if (s1[i] != s2[i]) {
                a[i] = 1;
            }
            for (int j = 0; j < n; j++) {
                dp[i][j][0] = INF;
                dp[i][j][1] = INF;
            }
        }
        if (a[0] == 0) {
            dp[0][0][0] = 0;
        } else {
            dp[0][1][1] = 0;
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i] == 0) {
                    if (j <= i) {
                        dp[i][j][0] = min(dp[i][j][0], min(dp[i - 1][j][0], dp[i - 1][j][1]));
                    }
                    if (j > 2) {
                        dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j - 2][0] + 1);
                    }
                    if (j != 0) {
                        dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j][1] + 1);
                        dp[i][j][1] = min(dp[i][j][1], dp[i - 1][j][0] + x);
                    }
                } else {
                    if (j != 0) {
                        dp[i][j][1] = min(dp[i][j][1], min(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1]));
                        dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j - 1][0] + 1);
                    }
                    if (j + 1 < n) {
                        dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j + 1][1] + 1);
                        dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j + 1][0] + x);
                    } 
                }
            } 
        }
        if (dp[n - 1][0][0] == INF) {
            return -1;
        }
        return dp[n - 1][0][0];
    }
};