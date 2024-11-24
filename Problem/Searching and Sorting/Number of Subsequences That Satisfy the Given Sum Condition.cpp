//https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
const long long M = 1e9 + 7;
class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<int> pw(n, 0);
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            pw[i] = (i == 0 ? 1 : pw[i - 1] * 2 % M);
            int l = 0, r = i, spl = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (nums[i] + nums[mid] > target) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                    spl = mid;
                }
            }
            if (spl == -1) {
                break;
            }
            ans = (ans + pw[i] - (i - spl - 1 < 0 ? 0 : pw[i - spl - 1]) + M) % M;
        }
        return ans;
    }
};
