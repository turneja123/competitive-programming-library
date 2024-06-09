//https://leetcode.com/contest/weekly-contest-400/problems/find-subarray-with-bitwise-and-closest-to-k/
class Solution {
public:
    int pref[100005][32];

    int get(int l, int r, int n) {
        int ans = 0;
        for (int j = 0; j < 31; j++) {
            int ct = pref[r][j];
            if (l > 0) {
                ct -= pref[l - 1][j];
            }
            if (ct == r - l + 1) {
                ans += 1 << j;
            }
        }
        return ans;
    }

    int minimumDifference(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 31; j++) {
                int b = 1 << j;
                int c = nums[i] & b;
                if (c != 0) {
                    pref[i][j] = 1;
                } else {
                    pref[i][j] = 0;
                }
                if (i != 0) {
                    pref[i][j] += pref[i - 1][j];
                }
            }
        }
        int ans = 1e9;
        for (int i = 0; i < n; i++) {
            int l = 0, r = i, best = 1e9, opti = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                int sum = get(mid, i, n);
                if (k - sum >= 0) {
                    l = mid + 1;
                    if (k - sum < best) {
                        opti = mid;
                        best = k - sum;
                    }
                } else {
                    r = mid - 1;
                    if (sum - k < best) {
                        opti = mid;
                        best = sum - k;
                    }
                }
            }
            for (int d = max(0, opti - 4); d <= min(i, opti + 4); d++) {
                best = min(best, abs(k - get(d, i, n)));
            }
            ans = min(ans, best);
        }
        return ans;
    }
};
