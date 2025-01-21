//https://leetcode.com/contest/weekly-contest-433/problems/paint-house-iv/
const int N = 1e5 + 5;
const long long INF = 1e18;
class Solution {
public:
    long long dp[N][3][3];

    long long minCost(int n, vector<vector<int>>& cost) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == j) {
                    continue;
                }
                dp[0][i][j] = cost[0][i] + cost[n - 1][j];
            }
        }
        for (int ind = 1; ind < n / 2; ind++) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (i == j) {
                        continue;
                    }
                    dp[ind][i][j] = INF;
                    for (int p = 0; p < 3; p++) {
                        if (p == i) {
                            continue;
                        }
                        for (int q = 0; q < 3; q++) {
                            if (p == q || q == j) {
                                continue;
                            }
                            dp[ind][i][j] = min(dp[ind][i][j], dp[ind - 1][p][q] + cost[ind][i] + cost[n - 1 - ind][j]);
                        }
                    }
                }
            }
        }
        long long ans = INF;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i != j) {
                    ans = min(ans, dp[n / 2 - 1][i][j]);
                }
            }
        }
        return ans;
    }
};
