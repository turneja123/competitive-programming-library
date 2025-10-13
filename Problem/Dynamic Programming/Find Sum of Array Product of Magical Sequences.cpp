//https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/
using ll = long long;
const ll M = 1e9 + 7;
const int N = 55;

ll dp[N][N][N][N]; //step, iskoristio, remain maska, bitova
ll inv[N];
ll fact[N];
ll factinv[N];

class Solution {
public:
    long long binomial(long long n, long long k) {
        return fact[n] * factinv[k] % M * factinv[n - k] % M;
    }

    long long modPow(long long a, long long y) {
        long long res = 1;
        while(y > 0) {
            if(y % 2 != 0) {
                res = (res * a) % M;
            }
            y /= 2;
            a = (a * a) % M;
        }
        return res;
    }

    int magicalSum(int m, int k, vector<int>& nums) {
        int n = nums.size();
        fact[0] = 1, factinv[0] = 1;
        for (int i = 1; i < N; i++) {
            inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
            fact[i] = fact[i - 1] * i % M;
            factinv[i] = factinv[i - 1] * inv[i] % M;
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                for (int mask = 0; mask < N; mask++) {
                    for (int b = 0; b <= k; b++) {
                        dp[i][j][mask][b] = 0;
                    }
                }
            }
        }

        dp[0][0][0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= m; j++) {
                for (int mask = 0; mask < N; mask++) {
                    for (int b = 0; b <= k; b++) {
                        if (dp[i][j][mask][b] == 0) {
                            continue;
                        }
                        for (int add = 0; add + j <= m; add++) {
                            int nw_m = add + mask;
                            int nw_b = b + (nw_m % 2 == 1);
                            if (nw_b > k) {
                                continue;
                            }
                            dp[i + 1][j + add][nw_m >> 1][nw_b] = (dp[i + 1][j + add][nw_m >> 1][nw_b] +
                            dp[i][j][mask][b] * binomial(m - j, add) % M * modPow(nums[i], add)) % M;

                        }
                    }
                }
            }
        }
        ll ans = 0;
        for (int mask = 0; mask < N; mask++) {
            for (int b = 0; b <= k; b++) {
                if (__builtin_popcount(mask) + b == k) {
                    ans = (ans + dp[n][m][mask][b]) % M;
                }
            }
        }
        return ans;
    }
};
