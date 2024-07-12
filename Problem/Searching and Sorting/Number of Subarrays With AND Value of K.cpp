//https://leetcode.com/contest/biweekly-contest-134/problems/number-of-subarrays-with-and-value-of-k/
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

    long long countSubarrays(vector<int>& nums, int k) {
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
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int l = 0, r = i, rt = -1, lf = n;
            while (l <= r) {
                int mid = (l + r) / 2;
                int sum = get(mid, i, n);
                if (sum > k) {
                    r = mid - 1;

                } else if (sum == k) {
                    rt = max(rt, mid);
                    l = mid + 1;

                } else {
                    l = mid + 1;
                }
            }

            if (rt == -1) {
                continue;
            }
            l = 0, r = i;

            while (l <= r) {
                int mid = (l + r) / 2;
                int sum = get(mid, i, n);
                if (sum > k) {
                    r = mid - 1;
                } else if (sum == k) {
                    lf = min(lf, mid);
                    r = mid - 1;

                } else {
                    l = mid + 1;
                }
            }
            if (lf == n) {
                continue;
            }
            ans += rt - lf + 1;
        }
        return ans;

    }
};
