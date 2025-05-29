//https://leetcode.com/contest/weekly-contest-451/problems/lexicographically-smallest-string-after-adjacent-removals/
const int N = 255;
class Solution {
public:
    int dp[N][N];
    string dp_s[N];

    bool good(char a, char b) {
        int x = a - 'a', y = b - 'a';
        if (abs(x - y) == 1 || abs(x - y) == 25) {
            return true;
        }
        return false;
    }

    string lex_min(string &a, string &b) {
        if (a[0] == '$') {
            return b;
        }
        if (b[0] == '$') {
            return a;
        }
        int n = a.size(), m = b.size();
        for (int i = 0; i < min(n, m); i++) {
            if (a[i] < b[i]) {
                return a;
            }
            if (a[i] > b[i]) {
                return b;
            }
        }
        if (n < m) {
            return a;
        }
        return b;
    }

    string calc(int i, int n, string &s) {
        if (i == n) {
            return "";
        }
        if (dp_s[i] != "$") {
            return dp_s[i];
        }
        for (int j = i; j < n; j++) {
            if (j == i || dp[i + 1][j]) {
                string cur = s[i] + calc(j + 1, n, s);
                dp_s[i] = lex_min(dp_s[i], cur);
            }
        }
        return dp_s[i];
    }

    string lexicographicallySmallestString(string s) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j + i < n; j++) {
                if (i % 2 == 0) {
                    continue;
                }
                if (i == 1) {
                    dp[j][j + 1] = good(s[j], s[j + 1]);
                    continue;
                }
                for (int k = j + 1; k <= j + i; k++) {
                    if (good(s[j], s[k])) {
                        int l = (j + 1 > k - 1 ? 1 : dp[j + 1][k - 1]), r = (k + 1 > j + i ? 1 : dp[k + 1][j + i]);
                        dp[j][j + i] |= l & r;
                    }
                }
            }
        }
        if (dp[0][n - 1]) {
            return "";
        }
        for (int i = 0; i < n; i++) {
            dp_s[i] = "$";
        }
        string ans = "$";
        for (int i = 0; i < n; i++) {
            if (dp_s[i] == "$" && (i == 0 || dp[0][i - 1])) {
                calc(i, n, s);
            }
            if (i == 0 || dp[0][i - 1]) {
                ans = lex_min(ans, dp_s[i]);
            }
        }
        return ans;
    }
};
