//https://leetcode.com/contest/weekly-contest-438/problems/maximize-the-distance-between-points-on-a-square/
const int N = 15000;
const int K = 14;

int up[K][N];
int add[K][N];

class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int need) {
        vector<long long> a;
        int n = points.size();
        for (int i = 0; i < n; i++) {
            if (points[i][1] == 0) {
                a.push_back((long long)points[i][0]);
            } else if (points[i][0] == side) {
                a.push_back((long long)side + points[i][1]);
            } else if (points[i][1] == side) {
                a.push_back((long long)2 * side + (side - points[i][0]));
            } else {
                a.push_back((long long)3 * side + (side - points[i][1]));
            }
        }
        sort(a.begin(), a.end());
        long long l = 1, r = 2 * side, ans = 0;
        while (l <= r) {
            long long d = (l + r) / 2;
            for (int i = 0; i < n; i++) {
                up[0][i] = -1;
                int lq = 1, rq = n - 1;
                while (lq <= rq) {
                    int mid = (lq + rq) / 2;
                    int j = (i + mid) % n;
                    if (i < j) {
                        if (a[j] - a[i] < d) {
                            lq = mid + 1;
                        } else {
                            if (4LL * side - (a[j] - a[i]) >= d) {
                                up[0][i] = j;
                                add[0][i] = mid;
                            }
                            rq = mid - 1;
                        }
                    } else {
                        if (4LL * side - (a[i] - a[j]) < d) {
                            lq = mid + 1;
                        } else {
                            if (a[i] - a[j] >= d) {
                                up[0][i] = j;
                                add[0][i] = mid;
                            }
                            rq = mid - 1;
                        }
                    }
                }
            }
            for (int k = 1; k < K; k++) {
                for (int i = 0; i < n; i++) {
                    int v = up[k - 1][i];
                    if (v == -1) {
                        up[k][i] = -1;
                        continue;
                    }
                    int ct = add[k - 1][i] + add[k - 1][v];
                    if (ct >= n) {
                        up[k][i] = -1;
                        continue;
                    }
                    int j = (i + ct) % n;
                    if (i < j) {
                        if (4LL * side - (a[j] - a[i]) < d) {
                            up[k][i] = -1;
                            continue;
                        }
                    } else {
                        if (a[i] - a[j] < d) {
                            up[k][i] = -1;
                            continue;
                        }
                    }
                    up[k][i] = up[k - 1][v];
                    add[k][i] = ct;
                }
            }
            int best = 0;
            for (int i = 0; i < n; i++) {
                int cur = 1, u = i, ct = 0;
                for (int k = K - 1; k >= 0; k--) {
                    if (up[k][u] == -1) {
                        continue;
                    }
                    if (ct + add[k][u] >= n) {
                        continue;
                    }
                    int j = (i + ct + add[k][u]) % n;
                    if (i < j) {
                        if (4LL * side - (a[j] - a[i]) < d) {
                            continue;
                        }
                    } else {
                        if (a[i] - a[j] < d) {
                            continue;
                        }
                    }
                    cur += 1 << k;
                    ct += add[k][u];
                    u = up[k][u];
                }
                best = max(best, cur);
            }
            if (best >= need) {
                ans = d;
                l = d + 1;
            } else {
                r = d - 1;
            }
        }
        return ans;
    }
};
