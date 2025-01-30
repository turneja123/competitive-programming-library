//https://leetcode.com/contest/weekly-contest-424/problems/minimize-the-maximum-adjacent-element-difference/
class Solution {
public:
    pair<int, int> intersect(int L, int R, int l, int r) {
        return make_pair(max(L, l), min(R, r));
    }


    int minDifference(vector<int>& nums) {
        int n = nums.size();
        bool pref = false, suf = false;
        int l = 0;
        while (l < n && nums[l] == -1) {
            pref = true;
            l++;
        }
        if (l == n) {
            return 0;
        }
        int r = n - 1;
        while (nums[r] == -1) {
            suf = true;
            r--;
        }
        vector<int> a;
        for (int i = l; i <= r; i++) {
            a.push_back(nums[i]);
        }
        n = a.size();
        int last = a[0], s = 0;
        int diff = 0, mn = 1e9;
        if (pref) {
            mn = min(mn, a[0]);
        }
        if (suf) {
            mn = min(mn, a[n - 1]);
        }
        vector<pair<int, int>> ones;
        vector<pair<int, int>> twos;

        for (int i = 1; i < n; i++) {
            if (a[i] == -1) {
                s++;
            } else if (s == 0) {
                diff = max(diff, abs(a[i] - a[i - 1]));
                last = a[i];
            } else if (s == 1) {
                ones.push_back(make_pair(last, a[i]));
                mn = min(mn, a[i]);
                mn = min(mn, last);
                s = 0;
                last = a[i];
            } else {
                twos.push_back(make_pair(last, a[i]));
                mn = min(mn, a[i]);
                mn = min(mn, last);
                s = 0;
                last = a[i];
            }
        }
        if (mn == 1e9) {
            return diff;
        }
        l = diff, r = 1e9; int ans = 1e9;
        while (l <= r) {
            int mid = (l + r) / 2;
            int lf = mn + mid;
            int L = lf, R = 2e9;
            if (pref) {
                if (abs(a[0] - lf) > mid) {
                    tie(L, R) = intersect(L, R, a[0] - mid, a[0] + mid);
                }
            }
            if (suf) {
                if (abs(a[n - 1] - lf) > mid) {
                    tie(L, R) = intersect(L, R, a[n - 1] - mid, a[n - 1] + mid);
                }
            }
            for (auto [x, y] : ones) {
                if (x > y) {
                    swap(x, y);
                }
                if (abs(x - lf) > mid || abs(y - lf) > mid) {
                    tie(L, R) = intersect(L, R, x - mid, x + mid);
                    tie(L, R) = intersect(L, R, y - mid, y + mid);
                }
            }
            for (auto [x, y] : twos) {
                if (x > y) {
                    swap(x, y);
                }
                if (x - lf > mid) {
                    tie(L, R) = intersect(L, R, x - mid, x + mid);
                    tie(L, R) = intersect(L, R, y - mid, y + mid);
                } else if (y - lf > mid) {
                    tie(L, R) = intersect(L, R, max(lf, x) - mid, max(lf, x) + mid);
                    tie(L, R) = intersect(L, R, y - mid, y + mid);
                }
            }

            if (L <= R) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }


        return ans;
    }
};
