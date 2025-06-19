https://leetcode.com/problems/maximize-subarray-gcd-score/
class Solution {
public:
    int freq[32];
    long long maxGCDScore(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> a(n, 0);
        for (int i = 0; i < n; i++) {
            int e = nums[i];
            while (e % 2 == 0) {
                e /= 2;
                a[i]++;
            }
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int mn = a[i];
            int g = nums[i];
            ans = max(ans, (long long)g * 2);
            freq[a[i]]++;
            for (int j = i + 1; j < n; j++) {
                g = __gcd(g, nums[j]);
                mn = min(mn, a[j]);
                freq[a[j]]++;
                if (freq[mn] <= k) {
                    ans = max(ans, (long long)g * 2 * (j - i + 1));
                } else {
                    ans = max(ans, (long long)g * (j - i + 1));
                }
            }
            for (int j = 0; j < 32; j++) {
                freq[j] = 0;
            }
        }
        return ans;
    }
};
