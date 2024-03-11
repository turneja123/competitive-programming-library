//https://leetcode.com/problems/painting-a-grid-with-three-different-colors/description/
class Solution {
public:
    int colorTheGrid(int m, int n) {
        vector<int> columns;
        int tot = 1;
        long long M = 1e9 + 7;
        for (int i = 0; i < m; i++) {
            tot *= 3;
        }
        for (int i = 0; i < tot; i++) {
            int temp = i, prev = i % 3, flag = 1;
            for (int j = 1; j < m; j++) {
                temp /= 3;
                int cur = temp % 3;
                if (cur == prev) {
                    flag = 0;
                }
                prev = cur;
            }
            if (flag) {
                columns.push_back(i);
            }
        }
        int k = columns.size();

        vector<vector<long long>> dp;
        dp.assign(n, vector<long long>(k, 0));
        for (int i = 0; i < k; i++) {
            dp[0][i] = 1;
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < k; j++) {
                for (int p = 0; p < k; p++) {
                    int l = columns[j], r = columns[p], flag = 1;
                    for (int d = 0; d < m; d++) {
                        if (l % 3 == r % 3) {
                            flag = 0;
                        }
                        l /= 3, r /= 3;
                    }
                    if (flag) {
                        dp[i][j] += dp[i - 1][p];
                        dp[i][j] %= M;
                    }
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < k; i++) {
            ans += dp[n - 1][i];
            ans %= M;
        }
        return ans;
    }
};
