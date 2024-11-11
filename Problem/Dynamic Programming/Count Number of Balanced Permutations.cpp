//https://leetcode.com/contest/weekly-contest-422/problems/count-number-of-balanced-permutations/
const int N = 85;
const long long M = 1e9 + 7;

class Solution {
public:
    long long dp[10][N][10 * N];
    long long nck[N][N];
    int freq[N];

    void precalc() {
        nck[0][0] = 1;
        for (int n = 1; n < N; n++) {
            nck[n][0] = nck[n][n] = 1;
            for (int k = 1; k < N; k++) {
                nck[n][k] = (nck[n - 1][k - 1] + nck[n - 1][k]) % M;
            }
        }
    }

    int countBalancedPermutations(string s) {
        if (!nck[0][0]) {
            precalc();
        }
        int n = s.size(), sum = 0;
        for (int i = 0; i < n; i++) {
            freq[s[i] - '0']++;
            sum += s[i] - '0';
        }
        if (sum % 2 == 1) {
            return 0;
        }
        int m = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = m; j >= 0; j--) {
                for (int d = 10 * j; d >= 0; d--) {
                    for (int add = 0; add <= freq[i] && j + add <= (n / 2) + 1; add++) {
                        dp[i][j + add][d + add * i] = (dp[i][j + add][d + add * i] + (i == 0 ? 1 : dp[i - 1][j][d]) * nck[j + add][add] % M * nck[m - j + freq[i] - add][freq[i] - add]) % M;
                    }
                }
            }
            m += freq[i];
        }
        return dp[9][n / 2][sum / 2];
    }
};
