//https://leetcode.com/problems/maximum-product-of-two-integers-with-no-common-bits/description/
const int N = 2e6 + 5;

int dp[N];

class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        int mx = 0;
        for (int x : nums) {
            mx = max(mx, x);
        }
        int K = 32 - __builtin_clz(mx);
        for (int i = 0; i < 1 << K; i++) {
            dp[i] = 0;
        }
        for (int x : nums) {
            dp[x] = x;
        }
        for (int k = 0; k < K; k++) {
            for (int j = 0; j < 1 << K; j++) {
                int c = j & (1 << k);
                if (c) {
                    dp[j] = max(dp[j], dp[j ^ (1 << k)]);
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < 1 << K; i++) {
            int mask = ((1 << K) - 1) ^ i;

            ans = max(ans, (long long)dp[i] * dp[mask]);
        }
        return ans;
    }
};
