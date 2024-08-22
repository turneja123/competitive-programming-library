//https://leetcode.com/contest/biweekly-contest-120/problems/count-the-number-of-incremovable-subarrays-ii/
class Solution {
public:
    int prefmx[100005];
    int sufmn[100005];

    long long incremovableSubarrayCount(vector<int>& a) {
        int n = a.size();
        if (n == 1) {
            return 1;
        }
        int mx = 0;
        for (int i = 0; i < n; i++) {
            mx = max(mx, a[i]);
            prefmx[i] = mx;
        }
        int mn = 2e9;
        for (int i = n - 1; i >= 0; i--) {
            mn = min(mn, a[i]);
            sufmn[i] = mn;
        }

        int r = n - 1;
        while (r > 0 && a[r - 1] < a[r]) {
            r--;
        }
        long long ans = min(n, n - r + 1);
        for (int l = 0; l < n; l++) {
            if (l > 0 && a[l] <= a[l - 1]) {
                break;
            }
            int L = max(r, l + 1), R = n - 1, spl = n;
            while (L <= R) {
                int mid = (L + R) / 2;
                if (prefmx[l] < sufmn[mid]) {
                    spl = mid;
                    R = mid - 1;
                } else {
                    L = mid + 1;
                }
            }
            ans += n - spl + 1 - (spl == l + 1);
        }
        return ans;
    }
};
