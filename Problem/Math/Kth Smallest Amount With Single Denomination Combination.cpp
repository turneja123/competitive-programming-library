//https://leetcode.com/problems/kth-smallest-amount-with-single-denomination-combination/description/
class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        sort(coins.begin(), coins.end());
        if (coins[0] == 1) {
            return k;
        }
        int n = coins.size();
        long long l = 1, r = 1e12, ans = 1e12;
        while (l <= r) {
            long long mid = (l + r) / 2, sum = 0;
            for (int j = 1; j < (1 << n); j++) {
                __int128 prod = 1;
                for (int i = 0; i < n; i++) {
                    int c = j & (1 << i);
                    if (c) {
                        if (prod == 1) {
                            prod = coins[i];
                        } else {
                            prod = prod * (__int128)coins[i] / __gcd(prod, (__int128)coins[i]);
                        }
                    }
                }
                if (__builtin_popcount(j) % 2 == 1) {
                    sum += mid / prod;
                } else {
                    sum -= mid / prod;
                }
            }
            if (sum >= k) {
                r = mid - 1;
                if (sum == k) {
                    ans = min(ans, mid);
                }
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};