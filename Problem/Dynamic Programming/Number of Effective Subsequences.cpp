//https://leetcode.com/problems/number-of-effective-subsequences/description/
using ll = long long;
const ll M = 1e9 + 7;
class Solution {
public:
    int countEffective(vector<int>& nums) {
        int k = 0, n = nums.size();
        int or_all = 0;
        for (int i = 0; i < n; i++) {
            k = max(k, 32 - __builtin_clz(nums[i]));
            or_all |= nums[i];
        }
        vector<int> dp(1 << k, 0);
        for (int i = 0; i < n; i++) {
            dp[nums[i]]++;
        }
        vector<ll> pw(n + 1, 0);
        pw[0] = 1;
        for (int i = 1; i <= n; i++) {
            pw[i] = pw[i - 1] * 2 % M;
        }

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < 1 << k; j++) {
                int c = (1 << i) & j;
                if (c) {
                    dp[j] = (dp[j] + dp[j ^ (1 << i)]);
                }
            }
        }
        vector<ll> ans(1 << k, 0);
        for (int j = 0; j < 1 << k; j++ ){
            ans[j] = pw[dp[j]] - 1;
        }

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < 1 << k; j++) {
                int c = (1 << i) & j;
                if (c) {
                    ans[j] = (ans[j] - ans[j ^ (1 << i)] + M) % M;
                }
            }
        }
        return (pw[n] - ans[or_all] + M) % M;
    }
};
