//https://leetcode.com/problems/count-subarrays-with-fixed-bounds/description/
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        long long ans = 0;
        int n = nums.size(), l = 0, mn = -1, mx = -1;
        for (int i = 0; i < n; i++) {
            if (nums[i] > maxK || nums[i] < minK) {
                l = i + 1;
                continue;
            }
            if (nums[i] == maxK) {
                mx = i;
            }
            if (nums[i] == minK) {
                mn = i;
            }
            if (mx >= l && mn >= l) {
                ans += min(mx, mn) - l + 1;
            }
        }
        return ans;
    }
};