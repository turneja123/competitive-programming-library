//https://leetcode.com/contest/weekly-contest-428/problems/minimum-operations-to-make-character-frequencies-equal/
class Solution {
public:
    int dp[26][2];
    int makeStringGood(string s) {
        vector<int> freq(26, 0);
        int n = s.size();
        for (int i = 0; i < n; i++) {
            freq[s[i] - 'a']++;
        }
        int ans = n;
        for (int k = 1; k <= n; k++) {
            dp[0][0] = 0, dp[0][1] = min(freq[0], abs(k - freq[0]));
            for (int i = 1; i < 26; i++) {
                dp[i][0] = dp[i - 1][1];
                dp[i][1] = dp[i - 1][1] + min(freq[i], abs(k - freq[i]));
                if (k < freq[i - 1] && k > freq[i]) {
                    int d = min(freq[i - 1] - k, k - freq[i]);
                    dp[i][1] = min(dp[i][1], dp[i - 1][0] + d + (freq[i - 1] - d - k) + (k - freq[i] - d));
                }
                if (k > freq[i - 1] && k > freq[i]) {
                    dp[i][1] = min(dp[i][1], dp[i - 1][0] + max(0, k - freq[i - 1] - freq[i]) + freq[i - 1]);
                }
            }
            ans = min(ans, dp[25][1]);
        }
        return ans;
    }
};
