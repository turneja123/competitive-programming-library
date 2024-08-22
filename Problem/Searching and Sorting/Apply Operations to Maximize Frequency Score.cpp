//https://leetcode.com/contest/weekly-contest-376/problems/apply-operations-to-maximize-frequency-score/
class Solution {
public:

    int maxFrequencyScore(vector<int>& a, long long k) {
        sort(a.begin(), a.end());
        int n = a.size();
        int l = 0, r = 1, ans = 1; long long cost = 0;
        for (int i = 0; i < n; i++) {
            while (l < i && cost > k) {
                cost -= a[i] - a[l];
                l++;
            }
            while (r < n && a[r] - a[i] + cost <= k) {
                cost += a[r] - a[i];
                r++;
            }
            while (l < i && r < n && a[r] - a[i] <= a[i] - a[l]) {
                cost += a[r] - a[i] - (a[i] - a[l]);
                l++, r++;
            }

            while (l > 0 && a[i] - a[l - 1] + cost <= k) {
                cost += a[i] - a[l - 1];
                l--;
            }

            ans = max(ans, r - l);
            if (i != n - 1) {
                cost -= (long long)(a[i + 1] - a[i]) * (r - i - 1);
                cost += (long long)(a[i + 1] - a[i]) * (i - l + 1);
            }
        }
        return ans;
    }
};
