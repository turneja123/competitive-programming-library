//https://leetcode.com/problems/minimum-steps-to-convert-string-with-operations/description/
const int N = 105;
class Solution {
public:
    int ct[26][26];
    int cost[N][N];
    int dp[N];
    int calc(string &a, string &b) {
        int n = a.size();
        int ans = n;
        for (int i = 0; i < n; i++) {
            int x = a[i] - 'a', y = b[i] - 'a';
            if (x == y) {
                ans--;
                continue;
            }
            ct[x][y]++;
            if (ct[y][x]) {
                ct[x][y]--;
                ct[y][x]--;
                ans--;
            }
        }
        for (int i = 0; i < n; i++) {
            int x = a[i] - 'a', y = b[i] - 'a';
            ct[x][y] = 0;
        }
        return ans;
    }

    int minOperations(string a, string b) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            string A = "", B = "";
            for (int j = i; j < n; j++) {
                A += a[j];
                B += b[j];
                cost[i][j] = calc(A, B);
                reverse(A.begin(), A.end());
                cost[i][j] = min(cost[i][j], 1 + calc(A, B));
                reverse(A.begin(), A.end());
            }
        }
        for (int i = 0; i < n; i++) {
            dp[i] = cost[0][i];
            for (int j = 0; j < i; j++) {
                dp[i] = min(dp[i], dp[j] + cost[j + 1][i]);
            }
        }
        return dp[n - 1];
    }
};
