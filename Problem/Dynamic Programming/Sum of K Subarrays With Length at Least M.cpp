//https://leetcode.com/contest/weekly-contest-439/problems/sum-of-k-subarrays-with-length-at-least-m/
const int N = 2005;
const int INF = 1e9;

int dp[N][N];
int pref[N];
int mx[N];
class Solution {
public:
    int maxSum(vector<int>& a, int k, int m) {
        int n = a.size();
        int l = -1;
        int sum = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = -INF;
            }
            mx[i] = -INF;
        }

        for (int i = 0; i < n; i++) {
            while (i - l >= m) {
                if (l == -1) {
                    mx[0] = 0;
                } else {
                    for (int j = 0; j <= k; j++) {
                        if (dp[l][j] != -INF) {
                            mx[j] = max(mx[j], dp[l][j] - pref[l]);
                        }
                    }
                }
                l++;
            }
            sum += a[i];
            pref[i] = sum;
            for (int j = 0; j <= k; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = 0;
                    continue;
                }
                if (i != 0) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                }
                if (j != 0 && mx[j - 1] != -INF) {
                    dp[i][j] = max(dp[i][j], mx[j - 1] + sum);
                }
            }
        }
        return dp[n - 1][k];
    }
};
