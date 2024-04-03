//https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-ii/description/
class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int ans = 1e9, n = nums.size(), sum = 0;
        vector<int> freq(32, 0);
        int l = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 32 && (1 << j) <= nums[i]; j++) {
                int c = nums[i] & (1 << j);
                if (c) {
                    freq[j]++;
                    if (freq[j] == 1) {
                        sum += 1 << j;
                    }
                }
            }
            while (l <= i && sum >= k) {
                ans = min(ans, i - l + 1);
                for (int j = 0; j < 32 && (1 << j) <= nums[l]; j++) {
                    int c = nums[l] & (1 << j);
                    if (c) {
                        freq[j]--;
                        if (freq[j] == 0) {
                            sum -= 1 << j;
                        }
                    }
                }
                l++;
            }
        }
        return (ans == 1e9) ? -1 : ans;
    }
};