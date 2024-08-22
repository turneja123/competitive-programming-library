//https://leetcode.com/contest/weekly-contest-403/problems/maximize-total-cost-of-alternating-subarrays/
class Solution {
public:
    long long pref[100005][2];
    long long dp[100005];
    long long mx[2];

    const long long INF = 1e18;

    long long maximumTotalCost(vector<int>& a) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            int add = ((i % 2 == 0) ? a[i] : -a[i]);
            pref[i][0] = ((i == 0) ? add : pref[i - 1][0] + add);
            pref[i][1] = ((i == 0) ? -add : pref[i - 1][1] - add);
        }
        mx[0] = -INF, mx[1] = -INF;
        for (int i = 0; i < n; i++) {
            dp[i] = pref[i][0];
            if (mx[1] != -INF) {
                dp[i] = max(dp[i], pref[i][1] + mx[1]);
            }
            if (mx[0] != -INF) {
                dp[i] = max(dp[i], pref[i][0] + mx[0]);
            }
            if (i % 2 == 0) {
                mx[1] = max(mx[1], dp[i] - pref[i][1]);
            } else {
                mx[0] = max(mx[0], dp[i] - pref[i][0]);
            }
        }
        return dp[n - 1];

    }
};
