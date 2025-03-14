//https://leetcode.com/contest/weekly-contest-379/problems/maximize-the-number-of-partitions-after-operations/
const int N = 1e4 + 5;
int pref[N][26];
int ct[26];
int dp[N][26][2];
class Solution {
public:
    int calc(int i, int n, int c, int flag, string &s, int k) {
        if (i == n) {
            return 0;
        }
        if (c == -1) {
            c = s[i] - 'a';
        }
        if (dp[i][c][flag] != -1) {
            return dp[i][c][flag];
        }

        int l = i, r = n - 1, up = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int cur = 0;
            for (int j = 0; j < 26; j++) {
                ct[j] = pref[mid][j];
                if (i != 0) {
                    ct[j] -= pref[i - 1][j];
                }
            }

            ct[s[i] - 'a']--;
            ct[c]++;
            for (int j = 0; j < 26; j++) {
                if (ct[j]) {
                    cur++;
                }
            }

            if (cur <= k) {
                up = mid + 1;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        dp[i][c][flag] = max(dp[i][c][flag], 1 + calc(up, n, -1, flag, s, k));

        l = i, r = n - 1, up = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int cur = 0, subs = 0;
            for (int j = 0; j < 26; j++) {
                ct[j] = pref[mid][j];
                if (i != 0) {
                    ct[j] -= pref[i - 1][j];
                }
            }

            ct[s[i] - 'a']--;
            ct[c]++;
            for (int j = 0; j < 26; j++) {
                if (ct[j]) {
                    cur++;
                }
                if (ct[j] > 1) {
                    subs = 1;
                }
            }

            if (cur <= k - 1) {
                if (cur == k - 1 && subs) {
                    up = mid + 1;
                }
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (flag && up != -1) {
            dp[i][c][flag] = max(dp[i][c][flag], 1 + calc(up, n, -1, 0, s, k));
        }

        l = i, r = n - 1, up = n;
        while (l <= r) {
            int mid = (l + r) / 2;
            int cur = 0;
            for (int j = 0; j < 26; j++) {
                ct[j] = pref[mid][j];
                if (i != 0) {
                    ct[j] -= pref[i - 1][j];
                }
            }

            ct[s[i] - 'a']--;
            ct[c]++;
            for (int j = 0; j < 26; j++) {
                if (ct[j]) {
                    cur++;
                }
            }

            if (cur >= k) {
                up = mid + 1;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        vector<int> freq(26, 0);
        for (int j = 0; j < 26; j++) {
            freq[j] = ct[j];
        }

        for (int j = 0; j < 26; j++) {
            if (freq[j] == 0 && flag) {
                dp[i][c][flag] = max(dp[i][c][flag], 1 + calc(up, n, j, 0, s, k));
            }
        }
        return dp[i][c][flag];
    }


    int maxPartitionsAfterOperations(string s, int k) {
        int n = s.size();
        if (k == 26) {
            return 1;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 26; j++) {
                if (i == 0) {
                    pref[i][j] = 0;
                } else {
                    pref[i][j] = pref[i - 1][j];
                }
                dp[i][j][0] = -1;
                dp[i][j][1] = -1;
            }
            pref[i][s[i] - 'a']++;
        }
        int ans = calc(0, n, -1, 1, s, k);
        for (int j = 0; j < 26; j++) {
            ans = max(ans, calc(0, n, j, 0, s, k));
        }
        return ans;
    }
};
