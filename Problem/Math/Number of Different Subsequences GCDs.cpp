//https://leetcode.com/contest/weekly-contest-235/problems/number-of-different-subsequences-gcds/
class Solution {
public:
    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        int mx = 0;
        for (int i = 0; i < nums.size(); i++) {
            mx = max(mx, nums[i]);
        }
        vector<int> freq(mx + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            freq[nums[i]] = 1;
        }
        int ans = 0;
        for (int i = mx; i >= 1; i--) {
            int g = 0;
            for (int j = i; j <= mx; j += i) {
                if (freq[j]) {
                    if (g == 0) {
                        g = j;
                    } else {
                        g = __gcd(g, j);
                    }
                }
            }
            if (g == i) {
                freq[i] = 1;
            }
            if (freq[i]) {
                ans++;
            }
        }
        return ans;
    }
};
