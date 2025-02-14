//https://leetcode.com/contest/weekly-contest-436/problems/maximize-the-minimum-game-score/
class Solution {
public:
    long long maxScore(vector<int>& points, int m) {
        int n = points.size();
        long long l = 1, r = 1e16, ans = 0;
        while (l <= r) {
            long long mid = (l + r) / 2;
            vector<long long> need(n);
            for (int i = 0; i < n; i++) {
                need[i] = (mid + points[i] - 1) / points[i];
            }
            long long cost = 1;
            need[0]--;
            for (int i = 0; i < n; i++) {
                if (i == n - 1) {
                    if (need[i] > 0) {
                        cost += need[i] * 2;
                    }
                    continue;
                }
                if (need[i] <= 0) {
                    cost++;
                    need[i + 1]--;
                    continue;
                }
                cost += 2 * need[i];
                need[i + 1] -= need[i];
                if (i + 1 == n - 1 && need[i + 1] <= 0) {
                    break;
                }
                cost++;
                need[i + 1]--;
            }
            if (cost <= m) {
                l = mid + 1;
                ans = mid;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};
