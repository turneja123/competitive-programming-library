//https://leetcode.com/contest/biweekly-contest-148/problems/manhattan-distances-of-all-arrangements-of-pieces/
const int N = 1e5 + 5;
const long long M = 1e9 + 7;

long long inv[N];
long long fact[N];
long long factinv[N];

class Solution {
public:
    long long binomial(long long n, long long k) {
        return fact[n] * factinv[k] % M * factinv[n - k] % M;
    }

    void precalc() {
        fact[0] = 1, factinv[0] = 1;
        for (int i = 1; i < N; i++) {
            inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
            fact[i] = fact[i - 1] * i % M;
            factinv[i] = factinv[i - 1] * inv[i] % M;
        }
        return;
    }

    long long sum(int n) {
        return (long long)n * (n + 1) / 2 % M;
    }

    int distanceSum(int m, int n, int k) {
        if (fact[0] == 0) {
            precalc();
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans += (sum(n - i - 1) * m + sum(m - j - 1) * n) % M * binomial(n * m - 2, k - 2) % M;
            }
        }
        return ans % M;
    }
};
