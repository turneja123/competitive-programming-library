//https://leetcode.com/contest/weekly-contest-430/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/
const int N = 1e5 + 5;
const long long M = 1e9 + 7;
long long inv[N];
long long fact[N];
long long factinv[N];
bool f = false;
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

    void precalc() {
        fact[0] = 1, factinv[0] = 1;
        for (int i = 1; i < N; i++) {
            inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
            fact[i] = fact[i - 1] * i % M;
            factinv[i] = factinv[i - 1] * inv[i] % M;
        }
        return;
    }

    int countGoodArrays(int n, int m, int k) {
        if (!f) {
            f = true;
            precalc();
        }
        if (m == 1) {
            if (k == n - 1) {
                return 1;
            } else {
                return 0;
            }
        }
        long long ans = binomial(n - 1, k) * m % M * modPow(m - 1, n - (k + 1)) % M;
        return ans;
    }
};
