//https://leetcode.com/contest/weekly-contest-425/problems/minimum-array-sum/
const int N = 105;
const int INF = 2e9;
int dp[N][N][N];

class Solution {
public:

    int minArraySum(vector<int>& nums, int lim, int op1, int op2) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= op1 + 1; j++) {
                for (int k = 0; k <= op2 + 1; k++) {
                    dp[i][j][k] = INF;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= op1; j++) {
                for (int k = 0; k <= op2; k++) {
                    int last = (i == 0 ? 0 : dp[i - 1][j][k]);
                    dp[i][j][k] = min(dp[i][j][k], last + nums[i]);
                    dp[i][j + 1][k] = min(dp[i][j + 1][k], last + nums[i] / 2 + nums[i] % 2);
                    if (nums[i] >= lim) {
                        dp[i][j][k + 1] = min(dp[i][j][k + 1], last + nums[i] - lim);
                        dp[i][j + 1][k + 1] = min(dp[i][j + 1][k + 1], last + (nums[i] - lim) / 2 + (nums[i] - lim) % 2);
                    }
                    if ((nums[i] / 2 + nums[i] % 2) >= lim) {
                        dp[i][j + 1][k + 1] = min(dp[i][j + 1][k + 1], last + (nums[i] / 2 + nums[i] % 2) - lim);
                    }
                }
            }
        }
        int ans = INF;
        for (int j = 0; j <= op1; j++) {
            for (int k = 0; k <= op2; k++) {
                ans = min(ans, dp[n - 1][j][k]);
            }
        }
        return ans;
    }
};
