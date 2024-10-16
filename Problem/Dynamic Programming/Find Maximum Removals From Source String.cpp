//https://leetcode.com/contest/biweekly-contest-141/problems/find-maximum-removals-from-source-string/
int dp[3005][3005];
class Solution {
public:
    int suf[3005];
    bool rem[3005];
    int maxRemovals(string a, string b, vector<int>& targetIndices) {
        for (int i : targetIndices) {
            rem[i] = true;
        }
        int n = a.size(), m = b.size(); int j = m - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (j >= 0 && a[i] == b[j]) {
                j--;
            }
            suf[i] = j;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = -1;
            }
        }
        int ans = 0;
        dp[0][0] = a[0] == b[0];
        if (rem[0]) {
            dp[0][1] = 0;
            if (n > 1 && suf[1] == -1) {
                ans = 1;
            }
        }
        for (int i = 1; i < n; i++) {
            if (dp[i - 1][0] == m) {
                dp[i][0] = m;
            } else {
                dp[i][0] = dp[i - 1][0] + (a[i] == b[dp[i - 1][0]]);
            }
            for (int j = 1; j <= n; j++) {
                if (dp[i - 1][j] == m) {
                    dp[i][j] = m;
                } else if (dp[i - 1][j] != -1) {
                    dp[i][j] = dp[i - 1][j] + (a[i] == b[dp[i - 1][j]]);
                }
                if (dp[i - 1][j - 1] != -1 && rem[i]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1]);
                }
                if (i == n - 1) {
                    if (dp[i][j] == m) {
                        ans = max(ans, j);
                    }
                } else {
                    if (dp[i][j] > suf[i + 1]) {
                        ans = max(ans, j);
                    }
                }
            }
        }
        return ans;
    }
};
