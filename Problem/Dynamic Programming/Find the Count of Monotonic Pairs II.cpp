//https://leetcode.com/contest/weekly-contest-410/problems/find-the-count-of-monotonic-pairs-ii/
class Solution {
public:
    const long long M = 1e9 + 7;

    long long dp[2005][1005];
    long long pref[2005][1005];

    int countOfPairs(vector<int>& a) {
        for (int i = 0; i <= a[0]; i++) {
            dp[0][i] = 1;
            pref[0][i] = i + 1;
        }
        int n = a.size();
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= a[i]; j++) {
                if (j - a[i] + a[i - 1] >= 0) {
                    dp[i][j] = pref[i - 1][min(j, j - a[i] + a[i - 1])];
                }
            }
            for (int j = 0; j <= a[i]; j++) {
                pref[i][j] = ((j == 0) ? dp[i][j] : pref[i][j - 1] + dp[i][j]) % M;
            }
        }
        long long ans = 0;
        for (int j = 0; j <= a[n - 1]; j++) {
            ans += dp[n - 1][j];
        }
        return ans % M;
    }
};
