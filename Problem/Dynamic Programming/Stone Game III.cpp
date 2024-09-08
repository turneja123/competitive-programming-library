//https://leetcode.com/problems/stone-game-iii/description/
const int N = 1e5;
class Solution {
public:
    const int INF = 1e9;
    int dp[2][N];
    int calc(int l, int n, int flag, vector<int> &a) {
        if (l >= n) {
            return 0;
        }
        if (dp[flag][l] != INF) {
            return dp[flag][l];
        }
        if (flag == 0) {
            int ans = INF;
            for (int i = l + 1; i <= l + 3; i++) {
                ans = min(ans, calc(i, n, flag ^ 1, a));
            }
            return dp[flag][l] = ans;
        } else {
            int ans = -INF, sum = a[l];
            for (int i = l + 1; i <= l + 3; i++) {
                ans = max(ans, sum + calc(i, n, flag ^ 1, a));
                if (i < n) {
                    sum += a[i];
                }
            }
            return dp[flag][l] = ans;
        }
    }


    string stoneGameIII(vector<int>& a) {
        int tot = 0, n = a.size();
        for (int i = 0; i < n; i++) {
            tot += a[i];
        }
        for (int i = 0; i < n; i++) {
            dp[0][i] = INF;
            dp[1][i] = INF;
        }
        int ans = -INF, sum = a[0];
        for (int i = 1; i <= 3; i++) {
            ans = max(ans, sum + calc(i, n, 0, a));
            if (i < n) {
                sum += a[i];
            }
        }
        if (tot < 0 && ans < 0 && ans * 2 - 1 == tot) {
            return "Alice";
        }
        if (ans > tot / 2) {
            return "Alice";
        } else if (ans == tot / 2 && abs(tot) % 2 == 0) {
            return "Tie";
        } else {
            return "Bob";
        }

    }
};
