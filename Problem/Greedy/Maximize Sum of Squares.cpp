//https://leetcode.com/contest/weekly-contest-366/problems/apply-operations-on-array-to-maximize-sum-of-squares/
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        vector<int> freqs(32, 0);
        int mx = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            int j = 1, ct = 0;
            mx = max(mx, nums[i]);
            while (j <= nums[i]) {
                int c = nums[i] & j;
                if (c == j) {
                    freqs[ct]++;
                }
                j *= 2;
                ct++;
            }
        }
        long long ans = 0, m = 1e9 + 7;
        for (int i = 0; i < k; i++) {
            long long cur = 0, j = 1;
            int ct = 0;
            while (j <= mx) {
                if (freqs[ct]) {
                    cur += j;
                    freqs[ct]--;
                }
                j *= 2;
                ct++;
            }
            ans = (ans + ((cur * cur) % m)) % m;
        }
        return ans; 
    }
};