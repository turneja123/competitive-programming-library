//https://leetcode.com/problems/subarrays-with-k-different-integers/description/
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        vector<int> freq(20005, 0);
        int ct = 0, n = nums.size(), more = n * (n + 1) / 2, less = 0;
        int l = 0;
        for (int i = 0; i < n; i++) {
            freq[nums[i]]++;
            if (freq[nums[i]] == 1) {
                ct++;
            }
            while (l <= i && ct >= k) {
                freq[nums[l]]--;
                if (freq[nums[l]] == 0) {
                    ct--;
                }
                l++;
            }
            less += i - l + 1;
        }
        for (int i = 0; i < n; i++) {
            freq[nums[i]] = 0;
        }
        l = 0, ct = 0;
        for (int i = 0; i < n; i++) {
            freq[nums[i]]++;
            if (freq[nums[i]] == 1) {
                ct++;
            }
            while (l <= i && ct > k) {
                freq[nums[l]]--;
                if (freq[nums[l]] == 0) {
                    ct--;
                }
                l++;
            }
            more -= i - l + 1;
        }
        int ans = n * (n + 1) / 2 - less - more;
        return ans;
    }
};