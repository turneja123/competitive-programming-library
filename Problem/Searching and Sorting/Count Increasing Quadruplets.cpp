//https://leetcode.com/contest/weekly-contest-330/problems/count-increasing-quadruplets/
int suf[4005][4005];
int pref[4005][4005];
class Solution {
public:
    long long countQuadruplets(vector<int>& a) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            a[i]--;
        }
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++) {
                pref[i][j] = ((i == 0) ? a[i] < j : pref[i - 1][j] + (a[i] < j));
            }
        }
        for (int j = 0; j < n; j++) {
            for (int i = n - 1; i >= 0; i--) {
                suf[i][j] = ((i == n - 1) ? a[i] > j : suf[i + 1][j] + (a[i] > j));
            }
        }
        long long ans = 0;
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                if (a[i] < a[j]) {
                    continue;
                }
                ans += (long long)pref[i - 1][a[j]] * suf[j + 1][a[i]];
            }
        }
        return ans;
    }
};
