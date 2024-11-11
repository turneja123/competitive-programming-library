//https://leetcode.com/contest/weekly-contest-423/problems/adjacent-increasing-subarrays-detection-ii/
class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& a) {
        int n = a.size();
        vector<int> pos;
        for (int i = 1; i < n; i++) {
            if (a[i] <= a[i - 1]) {
                pos.push_back(i);
            }
        }
        if (pos.empty()) {
            int ans = n / 2;
            return ans;
        }
        int ans = 1;
        for (int i = 0; i < n; i++) {
            int j = lower_bound(pos.begin(), pos.end(), i + 1) - pos.begin();
            if (j == pos.size()) {
                ans = max(ans, (n - i) / 2);
                continue;
            }
            int l = pos[j] - 1, r = ((j == pos.size() - 1) ? n - 1 : pos[j + 1] - 1);
            ans = max(ans, (l - i + 1) / 2);
            ans = max(ans, min(l - i + 1, r - l));
        }
        return ans;
    }
};
