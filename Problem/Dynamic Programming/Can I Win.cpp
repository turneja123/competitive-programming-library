//https://leetcode.com/problems/can-i-win/description/
const int K = 21;
class Solution {
public:
    int dp[1 << K];
    int calc(int mask, int cur, int flag, int n, int sum) {
        if (cur >= sum) {
            return !flag;
        }
        if (mask == ((1 << n) - 1)) {
            return 0;
        }
        if (dp[mask] != -1) {
            return dp[mask];
        }
        if (flag == 0) {
            int ans = 1;
            for (int i = 0; i < n; i++) {
                int c = mask & (1 << i);
                if (c == 0) {
                    ans = min(ans, calc(mask | (1 << i), cur + i + 1, flag ^ 1, n, sum));
                }
            }
            return dp[mask] = ans;
        } else {
            int ans = 0;
            for (int i = 0; i < n; i++) {
                int c = mask & (1 << i);
                if (c == 0) {
                    ans = max(ans, calc(mask | (1 << i), cur + i + 1, flag ^ 1, n, sum));
                }
            }
            return dp[mask] = ans;
        }
    }

    bool canIWin(int n, int sum) {
        int ans = 0;
        for (int i = 0; i < 1 << n; i++) {
            dp[i] = -1;
        }
        for (int i = 0; i < n; i++) {
            ans = max(ans, calc(1 << i, i + 1, 0, n, sum));
        }
        return ans;
    }
};
