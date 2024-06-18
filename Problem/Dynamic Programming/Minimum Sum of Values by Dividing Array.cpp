//https://leetcode.com/contest/weekly-contest-393/problems/minimum-sum-of-values-by-dividing-array/
class Solution {
public:
    const int INF = 1e9;
    int dp[10005][11];
    int pref[10005][18];
    int segtree[11][40005];

    int get(int l, int r, int n) {
        int ans = 0;
        for (int j = 0; j < 18; j++) {
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

    int rmq(int l, int r, int lq, int rq, int node, int n) {
        if (lq <= l && rq >= r) {
            return segtree[n][node];
        }

        if (l > rq || r < lq) {
            return INF;
        }

        int mid = (l + r) / 2;
        return min(rmq(l, mid, lq, rq, 2 * node + 1, n),
                   rmq(mid + 1, r, lq, rq, 2 * node + 2, n));
    }

    void update(int l, int r, int ind, long long val, int node, int n) {
        if (l == r) {
            segtree[n][node] = val;
            return;
        }

        int mid = (l + r) / 2;
        if (ind >= l && ind <= mid) {
            update(l, mid, ind, val, 2 * node + 1, n);
        } else {
            update(mid + 1, r, ind, val, 2 * node + 2, n);
        }
        segtree[n][node] = min(segtree[n][2 * node + 1], segtree[n][2 * node + 2]);
    }



    int minimumValueSum(vector<int>& a, vector<int>& b) {
        int n = a.size(), m = b.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 18; j++) {
                int b = 1 << j;
                int c = a[i] & b;
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
        for (int i = 0; i < n; i++) {
            if (get(0, i, n) == b[0]) {
                dp[i][0] = a[i];
            } else {
                dp[i][0] = INF;
            }
            update(0, n - 1, i, dp[i][0], 0, 0);
            for (int j = 1; j < m; j++) {
                int rq = -1;
                int l = 0, r = i;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    int sum = get(mid, i, n);
                    if (sum <= b[j]) {
                        if (sum == b[j]) {
                            rq = mid;
                        }
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                int lq = INF;
                l = 0, r = i;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    int sum = get(mid, i, n);
                    if (sum >= b[j]) {
                        if (sum == b[j]) {
                            lq = mid;
                        }
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                    }
                }
                lq--, rq--;
                if (rq < 0) {
                    dp[i][j] = INF;
                } else {
                    lq = max(lq, 0);
                    int best = rmq(0, n - 1, lq, rq, 0, j - 1);
                    if (best == INF) {
                        dp[i][j] = INF;
                    } else {
                        dp[i][j] = best + a[i];
                    }
                }
                update(0, n - 1, i, dp[i][j], 0, j);
            }
        }
        int ans = dp[n - 1][m - 1];
        if (ans == INF) {
            return -1;
        }

        return ans;

    }
};
