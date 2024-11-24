//https://leetcode.com/contest/weekly-contest-320/problems/number-of-beautiful-partitions/
const int N = 1005;
const long long M = 1e9 + 7;
long long dp[1005][1005];
long long add[1005];
bool prime[10];

class Solution {
public:
    int beautifulPartitions(string s, int k, int mn) {
        prime[2] = true, prime[3] = true, prime[5] = true, prime[7] = true;
        int l = -1, n = s.size();
        for (int i = 0; i < n; i++) {
            if (i - l >= mn) {
                if (l == -1) {
                    if (prime[s[0] - '0']) {
                        add[0] += 1;
                    }
                } else if (l != n - 1) {
                    for (int j = 1; j <= k; j++) {
                        if (prime[s[l + 1] - '0']) {
                            add[j] = (add[j] + dp[l][j]) % M;
                        }
                    }
                }
                l++;
            }
            if (!prime[s[i] - '0']) {
                for (int j = 1; j <= k; j++) {
                    dp[i][j] = add[j - 1];
                }
            }
        }
        int ans = dp[n - 1][k];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = 0;
            }
        }
        for (int j = 0; j <= k; j++) {
            add[j] = 0;
        }
        return ans;
    }
};
