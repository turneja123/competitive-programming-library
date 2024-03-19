//https://leetcode.com/contest/biweekly-contest-126/problems/find-the-sum-of-the-power-of-all-subsequences/
class Solution {
public:
    long long M = 1e9 + 7;
    long long dp[105][105][105]; // indeks, suma, broj uzetih
    long long powers[105];
    
    int sumOfPower(vector<int>& nums, int k) {
        int n = nums.size();
        long long pw = 1;
        for (int i = 0; i <= n; i++) {
            powers[i] = pw;
            pw = (pw * (long long)2) % M;
        }
        for (int i = 0; i < n; i++) {
            dp[i][0][0] = 1;
        }
        if (nums[0] <= k) {
            dp[0][nums[0]][1] = 1;
        }
        for (int i = 1; i < n; i++) {  
            for (int w = 1; w <= k; w++) {
                for (int j = 1; j <= n; j++) {
                    dp[i][w][j] = dp[i - 1][w][j];
                    if (w - nums[i] >= 0) {
                        dp[i][w][j] = (dp[i][w][j] + dp[i - 1][w - nums[i]][j - 1]) % M;
                    }

                }
            }
        }
        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = (ans + dp[n - 1][k][i] * powers[n - i]) % M;
        }
        return ans;
        
        
    }
};