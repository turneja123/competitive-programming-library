//https://leetcode.com/contest/biweekly-contest-142/problems/find-the-original-typed-string-ii/
const long long M = 1e9 + 7;
class Solution {
public:
    int possibleStringCount(string word, int k) {
        long long tot = 1;
        vector<int> a;
        int ct = 1;
        word += '1';
        for (int i = 1; i < word.size(); i++) {
            if (word[i - 1] != word[i]) {
                tot = tot * ct % M;
                a.push_back(ct);
                ct = 1;
            } else {
                ct++;
            }
        }
        int m = a.size();
        if (m >= k) {
            return tot;
        }
        vector<long long> dp(k, 0), pref(k, 1);
        for (int i = 0; i < m; i++) {
            for (int j = 1; j < k; j++) {
                int r = j - 1, l = max(0, j - a[i]);
                dp[j] = (pref[r] - (l == 0 ? 0 : pref[l - 1]) + M) % M;
            }
            for (int j = 0; j < k; j++) {
                pref[j] = (j == 0 ? dp[j] : (pref[j - 1] + dp[j]) % M) % M;
            }
        }
        return (tot - pref[k - 1] + M) % M;
    }
};
