//https://leetcode.com/contest/biweekly-contest-141/problems/find-the-number-of-possible-ways-for-an-event/
const int M = 1e9 + 7;
const int N = 1005;
long long part[N][N];
long long inv[N];
long long fact[N];
long long factinv[N];
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
        fact[0] = 1, fact[1] = 1;
        factinv[0] = 1, factinv[1] = 1;
        inv[1] = 1;
        for (int i = 2; i < N; i++) {
            inv[i] = M - (M / i) * inv[M % i] % M;
            fact[i] = fact[i - 1] * i % M;
            factinv[i] = factinv[i - 1] * inv[i] % M;
        }
        part[0][0] = 1;
        for (int i = 1; i < N; i++) {
            for (int j = 1; j < i; j++) {
                part[i][j] = (part[i - 1][j] * j +  part[i - 1][j - 1]) % M;
            }
            part[i][i] = 1;
        }
    }

    int numberOfWays(int n, int x, int y) {
        if (part[5][2] == 0) {
            precalc();
        }
        long long ans = 0;
        for (int i = 1; i <= x; i++) {
            ans += part[n][i] * modPow(y, i) % M * binomial(x, i) % M * fact[i] % M;
        }
        return ans % M;
    }
};
