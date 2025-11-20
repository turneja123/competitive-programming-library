//https://leetcode.com/problems/maximum-number-of-groups-with-increasing-length/description/
class Solution {
public:
    int maxIncreasingGroups(vector<int>& b) {
        int n = b.size();
        vector<long long> pref(n, 0);
        sort(b.begin(), b.end());
        for (int i = 0; i < n; i++) {
            pref[i] = (i == 0 ? 0 : pref[i - 1]) + b[i];
        }
        int l = 0, r = n - 1, ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            int can = 1;
            long long s = 0; int norm_s = 0;
            for (int i = n - 1; i >= mid; i--) {
                norm_s += 1;
                s = s + norm_s;
                int j = i - mid + 1;
                if (j > n) {
                    can = 0;
                    break;
                }
                if (pref[n - j] < s) {
                    can = 0;
                    break;
                }
            }
            if (can) {
                ans = norm_s;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};
