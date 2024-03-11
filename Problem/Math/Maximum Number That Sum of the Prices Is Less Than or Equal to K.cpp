//https://leetcode.com/problems/maximum-number-that-sum-of-the-prices-is-less-than-or-equal-to-k/description/
class Solution {
public:
    long long bits(long long n, long long k) {
        long long ans = (n >> (k + 1)) << k;
        if ((n >> k) & (long long)1) {
            ans += n & (((long long)1 << k) - 1);
        }
        return ans;
    }
    
    long long findMaximumNumber(long long k, int x) {
        long long l = 1, r = 1e16, ans = 0;
        while (l <= r) {
            long long mid = (l + r) / 2;
            long long sum = 0;
            for (int i = x; i < 62; i += x) {
                sum += bits(mid + 1, i - 1);
            }
            if (sum <= k) {
                ans = max(ans, mid);
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
        
    }
};