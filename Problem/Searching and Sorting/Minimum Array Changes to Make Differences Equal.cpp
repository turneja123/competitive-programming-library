//https://leetcode.com/contest/biweekly-contest-135/problems/minimum-array-changes-to-make-differences-equal/
class Solution {
public:
    int a[100005];
    int pref[100005];

    int minChanges(vector<int>& nums, int k) {
        map<int, int> mp;
        int n = nums.size(), m = n / 2;
        for (int i = 0; i < m; i++) {
            int mx = max(nums[i], nums[n - i - 1]), mn = min(nums[i], nums[n - i - 1]);
            int penalty = max(mx, k - mn);

            a[penalty + 1]++;
            int diff = abs(nums[i] - nums[n - i - 1]);
            mp[diff]++;
        }
        for (int i = 1; i <= k; i++) {
            pref[i] = pref[i - 1] + a[i];
        }
        int ans = m;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans = min(ans, m - it->second + pref[it->first]);
        }
        return ans;

    }
};
