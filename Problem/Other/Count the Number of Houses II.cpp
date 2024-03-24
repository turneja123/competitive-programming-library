//https://leetcode.com/problems/count-the-number-of-houses-at-a-certain-distance-ii/description/
class Solution {
public:
    void add(int l, int r, vector<long long> &pref) {
        pref[l]++;
        pref[r + 1]--;
        return;
    }
    
    vector<long long> countOfPairs(int n, int x, int y) {
        vector<long long> ans(n, 0);
        vector<long long> pref(n + 1, 0);
        if (x > y) {
            swap(x, y);
        }
        if (y - x <= 1) {
            for (int i = 0; i < n; i++) {
                ans[i] = (n - i - 1) * 2;
            }
            return ans;
        }
        
        int l = x, r = y;
        int mid = (r + l) / 2, j = mid;

        for (int i = 1; i <= n; i++) {
            if (i <= l) {
                add(1, mid - i, pref);
                add(l - i + 1, l - i + 1 + n - r, pref);
                add(l - i + 2, l - i + 1 + r - mid - 1, pref);
            } else if (i < mid) {
                j++;
                if (j == r) {
                    j--;
                }
                add(1, j - i, pref);
                add(i - l + 1, i - l + 1 + n - r, pref);
                add(i - l + 2, i - l + 1 + r - j - 1, pref);
            } else {
                add(1, n - i, pref);
            }
        }
        long long ct = 0;
        for (int i = 1; i <= n; i++) {
            ct += pref[i];
            ans[i - 1] = 2 * ct;
        }
        return ans;    
    }
};