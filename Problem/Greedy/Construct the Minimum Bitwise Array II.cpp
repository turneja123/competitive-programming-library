//https://leetcode.com/contest/biweekly-contest-141/problems/construct-the-minimum-bitwise-array-ii/
class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 2) {
                ans.push_back(-1);
                continue;
            }
            int cur = nums[i] - 1;
            int x = nums[i] / 2, p = x | (x + 1);
            if (p == nums[i]) {
                cur = nums[i] / 2;
            }
            int k = 2;
            while (k < cur) {
                int c = nums[i] & k;
                if (!c) {
                    k /= 2;
                    break;
                }
                k *= 2;
            }
            cur = min(cur, nums[i] - k);
            ans.push_back(cur);
        }
        return ans;
    }
};
