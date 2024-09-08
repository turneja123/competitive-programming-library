//https://leetcode.com/contest/weekly-contest-414/problems/maximize-score-of-numbers-in-ranges/
class Solution {
public:
    int maxPossibleScore(vector<int>& a, int d) {
        sort(a.begin(), a.end());
        long long l = 1, r = 2e9, ans = 0, n = a.size();
        while (l <= r) {
            long long mid = (l + r) / 2;
            long long can = 1, last = a[0];
            for (int i = 1; i < n && can; i++) {
                if (last + mid > a[i] + d) {
                    can = 0;
                }
                last = max((long long)a[i], last + mid);
            }
            if (can) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};
