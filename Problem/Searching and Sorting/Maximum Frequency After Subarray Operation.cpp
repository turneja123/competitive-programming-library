//https://leetcode.com/contest/weekly-contest-434/problems/maximum-frequency-after-subarray-operation/
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        vector<int> freq(51, 0);
        for (int i = 0; i < n; i++) {
            freq[nums[i]]++;
        }

        for (int j = -50; j <= 50; j++) {
            vector<int> a(n, 0);
            for (int i = 0; i < n; i++) {
                if (nums[i] == k) {
                    a[i] = -1;
                } else if (nums[i] + j == k) {
                    a[i] = 1;
                }
            }
            int best = 0, cur = 0;
            for (int i = 0; i < n; i++) {
                cur += a[i];
                best = max(best, cur);
                cur = max(cur, 0);
            }
            ans = max(ans, best);
        }
        return ans + freq[k];
    }
};
