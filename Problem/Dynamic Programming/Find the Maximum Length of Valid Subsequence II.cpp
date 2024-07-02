//https://leetcode.com/contest/weekly-contest-404/problems/find-the-maximum-length-of-valid-subsequence-ii/
class Solution {
public:
    int dp[2][3005];
    int mx[3005];
    int ans = 0;

    void calc(vector<int> &a, int k, int m) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            dp[0][i] = 0;
            dp[1][i] = 0;
        }
        for (int j = 0; j < m; j++) {
            mx[j] = -1;
        }
        mx[a[0] % m] = 1;
        for (int i = 1; i < n; i++) {
            dp[1][i] = max(dp[0][i - 1], dp[1][i - 1]);
            int j;
            if (a[i] % m <= k) {
                j = k - a[i] % m;
                if (mx[j] != -1) {
                    dp[0][i] = max(dp[0][i], mx[j] + 1);
                }

            } else {
                j = m + k - a[i] % m;
                if (mx[j] != -1) {
                    dp[0][i] = max(dp[0][i], mx[j] + 1);
                }
            }
            if (mx[a[i] % m] == -1) {
                mx[a[i] % m] = 1;
            }

            mx[a[i] % m] = max(mx[a[i] % m], dp[0][i]);
            ans = max({ans, dp[0][i], dp[1][i]});
        }
    }

    int maximumLength(vector<int>& a, int m) {
        int n = a.size();
        for (int k = 0; k < m; k++) {
            calc(a, k, m);
        }
        return ans;

    }
};
