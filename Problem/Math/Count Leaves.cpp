//https://codeforces.com/contest/2020/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const int SQ = 1e6 + 5;
const int N = 5e6 + 5;
const int D = 1;

long long dd, kk;

int deg, pos;
long long n, r;
bool composite[SQ];
int primes[SQ];
long long a[SQ];
long long poly[D];

long long pref[D][SQ];
long long g[D][SQ];

int block[2][SQ];

long long inv[N];
long long fact[N];
long long factinv[N];

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

int get(long long x) {
    return x <= r ? block[0][x] : block[1][n / x];
}

void sieve(int n) {
    for (int i = 2; i < n; i++) {
        if (!composite[i]) {
            primes[++pos] = i;
            long long pw = 1;
            for (int k = 0; k < deg; k++) {
                pref[k][pos] = (pref[k][pos - 1] + pw) % M;
                pw = pw * i % M;
            }
            for (int j = 2 * i; j < n; j += i) {
                composite[j] = true;
            }
        }
    }
    return;
}

long long f(int p, int k) {
    return binomial(kk * k + dd, dd);
}

long long calc(long long x, int j) {
    if (primes[j] >= x) {
        return 0;
    }
    int idx = get(x);
    long long ans = 0;
    for (int k = 0; k < deg; k++) {
        ans += poly[k] * g[k][idx] % M;
    }
    for (int k = 0; k < deg; k++) {
        ans -= poly[k] * pref[k][j] % M;
    }
    ans = (ans + M * 10) % M;
    for (int i = j + 1; i <= pos && primes[i] <= x / primes[i]; i++) {
        long long pw = primes[i];
        for (int e = 1; pw <= x; e++) {
            ans += f(primes[i], e) % M * (calc(x / pw, i) + (e != 1)) % M;
            if (pw > x / primes[i]) {
                break;
            }
            pw *= primes[i];
        }
    }
    return ans % M;
}

int main() {
    IOS;
    fact[0] = 1, fact[1] = 1;
    factinv[0] = 1, factinv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < N; i++) {
        inv[i] = M - (M / i) * inv[M % i] % M;
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> kk >> dd;
        deg = 1;
        poly[0] = binomial(kk + dd, dd);

        r = sqrt(n);
        while ((long long)r * r < n) {
            ++r;
        }
        while ((long long)r * r > n) {
            --r;
        }
        sieve(r + 1);
        int tot = 0;
        long long i = 1;
        while (i <= n) {
            long long x = n / i;
            a[++tot] = x;
            long long z = x % M;
            for (int k = 0; k < deg; k++) {
                if (k == 0) {
                    g[k][tot] = (z - 1 + M) % M;
                }
                if (k == 1) {
                    g[k][tot] = (z * (z + 1) % M * modPow(2, M - 2) - 1 + M) % M;
                }
                if (k == 2) {
                    g[k][tot] = (z * (z + 1) % M * (z * 2 + 1) % M * modPow(6, M - 2) - 1 + M) % M;

                }
            }
            if (x <= r) {
                block[0][x] = tot;
            }  else {
                block[1][n / x] = tot;
            }
            i = n / x + 1;
        }
        for (int i = 1; i <= pos; i++) {
            for (int j = 1; j <= tot && primes[i] <= a[j] / primes[i]; j++) {
                int idx = get(a[j] / primes[i]);
                long long pw = 1;
                for (int k = 0; k < deg; k++) {
                    g[k][j] = (g[k][j] - pw * (g[k][idx] - pref[k][i - 1] + M) % M + M) % M;
                    pw = (pw * primes[i]) % M;
                }
            }
        }
        long long ans = (calc(n, 0) + 1) % M;
        cout << ans << endl;
        pos = 0;
    }
    return 0;
}
