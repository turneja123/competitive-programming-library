//https://leetcode.com/contest/weekly-contest-301/problems/count-the-number-of-ideal-arrays/
const long long M = 1e9 + 7;
const int N = 1e5 + 5;

long long inv[N];
long long fact[N];
long long factinv[N];

class Solution {
public:
    long long binomial(long long n, long long k) {
        return fact[n] * factinv[k] % M * factinv[n - k] % M;
    }

    long long stars(long long n, long long k) {
        return binomial(n + k - 1, n);
    }

    void precalc() {
        fact[0] = 1, factinv[0] = 1;
        for (int i = 1; i < N; i++) {
            inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
            fact[i] = fact[i - 1] * i % M;
            factinv[i] = factinv[i - 1] * inv[i] % M;
        }
    }

    int idealArrays(int n, int maxValue) {
        if (fact[0] == 0) {
            precalc();
        }
        long long sum = 0;
        for (int t = 1; t <= maxValue; t++) {
            int m = t;
            long long ans = 1;
            for (int i = 2; i <= sqrt(m); i++) {
                int e = 0;
                while (m % i == 0) {
                    e++;
                    m /= i;
                }
                if (e > 0) {
                    ans = ans * stars(e, n) % M;
                }
            }
            if (m > 1) {
                ans = ans * n % M;
            }
            sum = (sum + ans) % M;
        }
        return sum;
    }
};
