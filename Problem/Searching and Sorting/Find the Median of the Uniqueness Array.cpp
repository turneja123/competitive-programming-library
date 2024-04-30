//https://leetcode.com/problems/find-the-median-of-the-uniqueness-array/description/
class Solution {
public:
    int medianOfUniquenessArray(vector<int>& nums) {
        long long n = nums.size(), targ = (n * (n + 1) / 2) / 2 + (n * (n + 1) / 2) % 2;
        int l = 1, r = n, ans = n;
        while (l <= r) {
            int mid = (l + r) / 2;
            long long cur = 0;
            int ct = 0, lp = 0;
            vector<int> freqs(100005, 0);
            for (int i = 0; i < n; i++) {
                freqs[nums[i]]++;
                if (freqs[nums[i]] == 1) {
                    ct++;
                }
                while (ct > mid) {
                    freqs[nums[lp]]--;
                    if (freqs[nums[lp]] == 0) {
                        ct--;
                    }
                    lp++;
                }
                cur += i - lp + 1;
            }
            if (cur >= targ) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
        
    }
};