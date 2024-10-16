//https://judge.yosupo.jp/problem/sum_of_totient_function
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 998244353;
const int SQ = 2e5 + 5;
const int D = 2;

int deg, pos;
long long n, r;
bool composite[SQ];
int primes[SQ];
long long a[SQ];
long long poly[D];

long long pref[D][SQ];
long long g[D][SQ];

int block[2][SQ];

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

long long f(int p, long long inv, int k, long long pw) {
    pw %= M;
    return (pw - pw * inv % M + M) % M;
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
        long long pw = primes[i], inv = modPow(primes[i], M - 2);
        for (int e = 1; pw <= x; e++) {
            ans += f(primes[i], inv, e, pw) * (calc(x / pw, i) + (e != 1)) % M;
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
    deg = 2;
    poly[0] = -1, poly[1] = 1;
    poly[0] = (poly[0] + M) % M;
    cin >> n;
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
    cout << ans;
    return 0;
}
