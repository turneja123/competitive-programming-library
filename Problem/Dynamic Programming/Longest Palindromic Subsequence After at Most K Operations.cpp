//https://leetcode.com/contest/weekly-contest-439/problems/longest-palindromic-subsequence-after-at-most-k-operations/
const int N = 205;
const int INF = 1e9;
int dp[N][N][N];
class Solution {
public:
    int cost[26][26];

    int dist(int l, int r) {
        if (l > r) {
            swap(l, r);
        }
        return min(r - l, 26 - (r - l));
    }

    int calc(int l, int r, int k, int m, string &s) {
        if (k < 0) {
            return -INF;
        }
        if (l > r) {
            return 0;
        }
        if (l == r) {
            return 1;
        }
        if (dp[l][r][k] != -1) {
            return dp[l][r][k];
        }
        dp[l][r][k] = max(calc(l + 1, r, k, m, s), calc(l, r - 1, k, m, s));
        dp[l][r][k] = max(dp[l][r][k], calc(l + 1, r - 1, k, m, s));
        dp[l][r][k] = max(dp[l][r][k], 2 + calc(l + 1, r - 1, k - cost[s[l] - 'a'][s[r] - 'a'], m, s));
        return dp[l][r][k];
    }

    int longestPalindromicSubsequence(string s, int m) {
        for (int i = 0; i < 26; i++) {
            for(int j = 0; j < 26; j++) {
                cost[i][j] = INF;
                for (int k = 0; k < 26; k++) {
                    cost[i][j] = min(cost[i][j], dist(i, k) + dist(j, k));
                }
            }
        }
        int n = s.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k <= m; k++) {
                    dp[i][j][k] = -1;
                }
            }
        }
        return calc(0, n - 1, m, m, s);
    }
};
