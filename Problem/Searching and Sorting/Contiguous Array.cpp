//https://leetcode.com/problems/contiguous-array/description/
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> mp;
        int sum = 0, ans = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            if (mp.find(sum) == mp.end()) {
                mp[sum] = i;
            }
            if (nums[i] == 0) {
                sum--;
            } else {
                sum++;
            }
            if (mp.find(sum) != mp.end()) {
                ans = max(ans, i - mp[sum] + 1);
            }
        }
        return ans;
    }
};