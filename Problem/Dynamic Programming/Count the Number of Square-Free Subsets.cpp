//https://leetcode.com/contest/weekly-contest-333/problems/count-the-number-of-square-free-subsets/
const int K = 10;
const long long M = 1e9 + 7;
vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
long long dp[1005][1 << K];
class Solution {
public:
    int squareFreeSubsets(vector<int>& nums) {
        int n = nums.size();
        for (int j = 0; j < 1 << K; j++) {
            dp[0][j] = 0;
        }
        for (int i = 0; i < n; i++) {
            int a = nums[i], mask = 0, can = 1;
            for (int j = 0; j < primes.size(); j++) {
                int e = 0;
                while (a % primes[j] == 0) {
                    a /= primes[j];
                    e++;
                }
                if (e == 1) {
                    mask += 1 << j;
                } else if (e > 1) {
                    can = 0;
                }
            }
            if (i != 0) {
                for (int j = 0; j < 1 << K; j++) {
                    dp[i][j] = dp[i - 1][j];
                }
            }
            if (!can) {
                continue;
            }
            dp[i][mask] = (dp[i][mask] + 1) % M;
            if (i != 0) {
                for (int j = 0; j < 1 << K; j++) {
                    int c = j & mask;
                    if (!c) {
                        dp[i][j | mask] = (dp[i][j | mask] + dp[i - 1][j]) % M;
                    }
                }
            }
        }
        long long ans = 0;
        for (int j = 0; j < 1 << K; j++) {
            ans += dp[n - 1][j];
        }
        return ans % M;


    }
};
