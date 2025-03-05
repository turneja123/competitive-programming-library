//https://leetcode.com/contest/biweekly-contest-151/problems/find-minimum-cost-to-remove-array-elements/
const int N = 1005;
const long long INF = 1e18;
long long dp[N][N];
class Solution {
public:
    int minCost(vector<int>& a) {
        int n = a.size();
        if (n == 1) {
            return a[0];
        }
        if (n == 2) {
            return max(a[0], a[1]);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = INF;
            }
        }
        dp[0][0] = max(a[1], a[2]);
        dp[0][1] = max(a[0], a[2]);
        dp[0][2] = max(a[0], a[1]);
        int last = 0;
        for (int i = 3; i < n; i += 2) {
            for (int j = 0; j < n; j++) {
                if (dp[last][j] == INF) {
                    continue;
                }
                if (i == n - 1) {
                    dp[i][j] = min(dp[i][j], dp[last][j] + (long long)max(a[j], a[i]));
                } else {
                    dp[i][j] = min(dp[i][j], dp[last][j] + max(a[i], a[i + 1]));
                    dp[i][i] = min(dp[i][i], dp[last][j] + max(a[j], a[i + 1]));
                    dp[i][i + 1] = min(dp[i][i + 1], dp[last][j] + max(a[j], a[i]));
                }
            }
            last = i;
        }
        long long ans = INF;
        for (int j = 0; j < n; j++) {
            if (n % 2 == 0) {
                ans = min(ans, dp[last][j]);
            } else {
                ans = min(ans, dp[last][j] + a[j]);
            }
        }
        return ans;
    }
};
