//https://leetcode.com/contest/biweekly-contest-59/problems/number-of-ways-to-separate-numbers/
const int N = 3505;
const long long M = 1e9 + 7;
int dp[N][N];
int pref[N][N];
int lcp[N][N];

class Solution {
public:
    int numberOfCombinations(string str) {
        if (str[0] == '0') {
            return 0;
        }
        int n = str.size();
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (str[i] == str[j]) {
                    lcp[i][j] = 1 + lcp[i + 1][j + 1];
                } else {
                    lcp[i][j] = 0;
                }
            }
        }
        dp[0][1] = 1;
        for (int j = 1; j <= n; j++) {
            pref[0][j] = 1;
        }
        for (int i = 1; i < n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (str[j + 1] == '0') {
                    continue;
                }
                int s = i - j;
                dp[i][s] = pref[j][s - 1];
                if (i + 1 >= 2 * s) {
                    int r = j + 1, l = r - s;
                    int p = lcp[l][r];
                    if (p >= s || str[l + p] < str[r + p]) {
                        dp[i][s] = (dp[i][s] + dp[j][s]) % M;
                    }
                }
            }
            dp[i][i + 1] = 1;
            for (int s = 1; s <= n; s++) {
                pref[i][s] = (pref[i][s - 1] + dp[i][s]) % M;
            }
        }
        long long ans = 0;
        for (int s = 1; s <= n; s++) {
            ans = (ans + dp[n - 1][s]) % M;
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = 0, pref[i][j] = 0, lcp[i][j] = 0;
            }
        }
        return ans;
    }
};
