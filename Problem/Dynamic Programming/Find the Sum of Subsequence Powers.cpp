//https://leetcode.com/problems/find-the-sum-of-subsequence-powers/description/
class Solution {
public:
    long long M = 1e9 + 7;
    int dp[52 * 52][52][52]; // najmanja razlika, poslednji, velicina
    int dp_prev[52 * 52][52][52];

    int sumOfPowers(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for (int diff = 0; diff < n * n; diff++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j <= n; j++) {
                    dp_prev[diff][i][k] = -1;
                }
            }
        }
        dp_prev[0][0][0] = 1;
        dp_prev[0][0][1] = 1;
        for (int i = 1; i < n; i++) {
            for (int diff = 0; diff < n * n && diff / n <= i; diff++) {
                for (int prv = 0; prv <= i; prv++) {
                    for (int j = 0; j <= i + 1; j++) {
                        if (dp_prev[diff][prv][j] != -1) {
                            dp[diff][prv][j] = (dp[diff][prv][j] + dp_prev[diff][prv][j]) % M;

                            if (j == 0) {
                                dp[i * n][i][1] = (dp[i * n][i][1] + dp_prev[diff][prv][0]) % M;
                                continue;
                            }
                            if (j == 1) {
                                dp[prv * n + i][i][2] = (dp[prv * n + i][i][2] + dp[diff][prv][1]) % M;
                                continue;
                            }
                            int d1 = nums[diff % n] - nums[diff / n];
                            int d2 = nums[i] - nums[prv];
                            if (d2 < d1) {
                                dp[prv * n + i][i][j + 1] = (dp[prv * n + i][i][j + 1] + dp[diff][prv][j]) % M;
                            } else {
                                dp[diff][i][j + 1] = (dp[diff][i][j + 1] + dp[diff][prv][j]) % M;
                            }

                        }
                       
                    }
                }
            }
            for (int diff = 0; diff < n * n && diff / n <= i; diff++) {
                for (int prv = 0; prv <= i; prv++) {
                    for (int j = 0; j <= i + 1; j++) {
                        if (dp[diff][prv][j] == 0) {
                            dp_prev[diff][prv][j] = -1;
                        } else {
                            dp_prev[diff][prv][j] = dp[diff][prv][j];
                        }
                        dp[diff][prv][j] = 0;
                    }
                }
            }
        }
        long long ans = 0;
        for (int diff = 0; diff < n * n; diff++) {
            for (int prv = 0; prv < n; prv++) {
                if (dp_prev[diff][prv][k] == -1) {
                    continue;
                }
                ans = (ans + (long long)dp_prev[diff][prv][k] * (long long)(nums[diff % n]- nums[diff / n])) % M;
            }
        }
        return ans;

    }
};