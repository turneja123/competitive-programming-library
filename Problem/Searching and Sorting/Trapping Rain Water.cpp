//https://leetcode.com/problems/trapping-rain-water/description/
class Solution {
public:
    int l[100005];
    int r[100005];

    int trap(vector<int>& a) {
        int n = a.size();
        int mx = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            l[i] = mx;
            mx = max(mx, a[i]);
        }
        mx = 0;
        for (int i = n - 1; i >= 0; i--) {
            r[i] = mx;
            mx = max(mx, a[i]);
        }
        for (int i = 0; i < n; i++) {
            ans += max(0, min(l[i], r[i]) - a[i]);
        }
        return ans;
    }
};
