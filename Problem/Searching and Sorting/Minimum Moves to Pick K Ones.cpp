//https://leetcode.com/contest/weekly-contest-389/problems/minimum-moves-to-pick-k-ones/
class Solution {
public:
    long long prefones[100005];
    long long pref[100005];
    long long INF = 1e12;
    
    long long sum(int l, int r, int i, int n) {
        if (r < 0) {
            return 0;
        }
        r = min(r, n - 1);
        if (l > r) {
            return 0;
        }
        long long ans = 0;
        if (i == 0) {
            ans = prefones[r] - ((l > 0) ? prefones[l - 1] : 0);
            return ans;
        } 
        ans = pref[r] - ((l > 0) ? pref[l - 1] : 0);
        return ans;
    }
    bool chk (int i, vector<int> &nums) {
        if (i < 0 || i >= nums.size()) {
            return false;
        }
        return nums[i] == 1;
    }
    
    long long minimumMoves(vector<int>& nums, int k, int maxChanges) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            prefones[i] = ((i == 0) ? nums[i] : prefones[i - 1] + nums[i]);
            pref[i] = ((i == 0) ? ((nums[i] == 1) ? i : 0) : pref[i - 1] + ((nums[i] == 1) ? i : 0));
           // cout << prefones[i] << " " << pref[i] << endl;
        }
        long long ans = INF;
        if (n == 2) {
            if (prefones[1] == 2) {
                if (k == 1) {
                    return 0;
                }
                return (k - 2) * 2 + 1;
            }
            if (prefones[1] == 1) {
                return (k - 1) * 2;
            }
            return k * 2;
        }
        for (int i = 0; i < n; i++) {
            int l = 0, r = n - 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                int cur = 0;
                if (mid == 0) {
                    if (nums[i] == 1 && k == 1) {
                        ans = 0;
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                    }
                } else if (mid == 1) {
                    cur = sum(i - mid, i + mid, 0, n);
                    if (cur >= k) {
                        long long x = cur;
                        if (cur > k) {
                            x--;
                        }
                        if (chk(i, nums)) {
                            x--;
                        }
                        ans = min(ans, x);
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                    }
                } else if (mid == 2) {
                    cur = sum(i - mid, i + mid, 0, n);
                    if (cur + maxChanges < k) {
                        l = mid + 1;
                    } else {
                        long long x = 0, y = k;
                        if (chk(i, nums)) {
                            y--;
                        }
                        if (chk(i - 1, nums)) {
                            x++, y--;
                        }
                        if (chk(i + 1, nums)) {
                            x++, y--;
                        }
                        if (y <= 0) {
                            ans = min(ans, x);
                        } else {
                            ans = min(ans, x + y * 2);
                        }
                        r = mid - 1;
                    }
                } else {
                    cur = sum(i - mid, i + mid, 0, n) + maxChanges;
                    if (cur < k) {
                        l = mid + 1;
                    } else {
                        int lq = i - mid, rq = i + mid;
                        if (cur > k) {
                            if (chk(lq, nums)) {
                                lq++;
                            } else if (chk(rq, nums)) {
                                rq--;
                            }
                        }
                        long long ctl = sum(lq, i - 1, 0, n), ctr = sum(i + 1, rq, 0, n);
                        long long suml = sum(lq, i - 1, 1, n), sumr = sum(i + 1, rq, 1, n);
                        ans = min(ans, (long long)i * ctl - suml + sumr - (long long)i * ctr + (long long)2 * maxChanges);
                        r = mid - 1;
                    }
                }
            }
        }
        return ans;
    }
};