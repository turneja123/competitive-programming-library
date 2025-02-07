//https://leetcode.com/contest/weekly-contest-435/problems/minimum-increments-for-target-multiples-in-an-array/
const int N = 1e5 + 5;
class Solution {
public:
    long long lcm[16];
    long long dp[N][16];

    int minimumIncrements(vector<int>& nums, vector<int>& target) {
        int n = nums.size(), m = target.size();
        for (int j = 1; j < 1 << m; j++) {
            lcm[j] = 1;
            for (int i = 0; i < m; i++) {
                int c = j & (1 << i);
                if (c) {
                    lcm[j] = lcm[j] * target[i] / __gcd(lcm[j], (long long)target[i]);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            dp[i][0] = 0;
            for (int j = 1; j < 1 << m; j++) {
                if (i == 0) {
                    long long md = (long long)nums[i] % lcm[j];
                    dp[i][j] = (lcm[j] - md) % lcm[j];
                } else {
                    dp[i][j] = dp[i - 1][j];
                    for (int s = j; s; s = (s - 1) & j) {
                        long long md = (long long)nums[i] % lcm[s];
                        dp[i][j] = min(dp[i][j], dp[i - 1][s ^ j] + (lcm[s] - md) % lcm[s]);
                    }

                }
            }
        }
        return dp[n - 1][(1 << m) - 1];
    }
};
