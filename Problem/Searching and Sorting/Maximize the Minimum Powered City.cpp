//https://leetcode.com/contest/biweekly-contest-95/problems/maximize-the-minimum-powered-city/
const int N = 1e5 + 5;
class Solution {
public:
    long long diff[N];

    long long maxPower(vector<int>& stations, int p, int k) {
        int n = stations.size();
        for (int i = 0; i < n; i++) {
            int l = max(0, i - p);
            diff[l] += stations[i];
            if (i + p + 1 < n) {
                diff[i + p + 1] -= stations[i];
            }
        }
        long long l = 0, r = 2e10, ans = 0;
        while (l <= r) {
            long long mid = (l + r) / 2;
            long long need = 0, sum = 0;
            vector<long long> add(n, 0);
            for (int i = 0; i < n; i++) {
                sum += diff[i] + add[i];
                if (sum < mid) {
                    int j = i + 2 * p + 1;
                    if (j < n) {
                        add[j] -= mid - sum;
                    }
                    need += mid - sum;
                    sum = mid;
                }
            }
            if (need <= k) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};
