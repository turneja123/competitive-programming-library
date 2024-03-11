//https://leetcode.com/problems/count-of-interesting-subarrays/description/
class Solution {
public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        int n = nums.size();
        vector<int> a(n, 0);
        for (int i = 0; i < n; i++) {
            if (nums[i] % modulo == k) {
                a[i] = 1;
            }
        }
        if (k > n) {
            return 0;
        }
        vector<int> pref(1e5 + 5, 0);
        long long ans = 0, ct = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                ct++;
                if (k == 1 || modulo == 1) {
                    ans++;
                }
            } else if (k == 0 || modulo == 1) {
                ans++;
            }
            if (ct >= k) {
                int target = (ct - k) % modulo;
                ans += pref[target];
            }
            if (a[i] == 1) {
                pref[(ct - 1) % modulo]++;
            } else {
                pref[ct % modulo]++; 
            }
        }
        return ans;
        
    }
};