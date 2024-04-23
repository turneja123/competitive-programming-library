//https://www.codechef.com/problems/XETF
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 1e4 + 5;
const long long M = 1e9 + 7;

long long y[K];
long long pref[K];
long long suf[K];
long long inv[K];
long long modinv[K];

long long modPow(long long a, long long y, long long m) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}

long long lagrange(long long n, int k) {
    int deg = k + 1;
    if (n <= deg) {
        return y[n];
    }
    inv[0] = 1;
    pref[0] = n % M, suf[deg] = (n - deg) % M;
    for (int i = 1; i < deg; i++) {
        pref[i] = (pref[i - 1] * ((n - i) % M)) % M;
    }
    for (int i = deg - 1; i >= 0; i--) {
        suf[i] = (suf[i + 1] * ((n - i) % M)) % M;
    }
    for (int i = 1; i <= deg; i++) {
        inv[i] = (inv[i - 1] * modinv[i]) % M;
    }
    long long ans = 0;
    for (int i = 0; i <= deg; i++) {
        long long num, denom;
        if (i == 0) {
            num = suf[1];
        } else if (i == deg) {
            num = pref[deg - 1];
        } else {
            num = pref[i - 1] * suf[i + 1] % M;
        }
        denom = inv[i] * inv[deg - i] % M;
        if ((deg - i) % 2 == 0) {
            ans = (ans + ((y[i] * num % M) * denom) % M) % M;
        } else {
            ans = (ans - ((y[i] * num % M) * denom) % M + M) % M;
        }
    }
    return ans;
}

vector<int> primes = {2, 3, 5, 7, 11, 13, 17};
set<long long> factors;

__int128 mult(__int128 a, __int128 b, __int128 mod) {
    return (__int128)a * b % mod;
}

__int128 f(__int128 x, __int128 c, __int128 mod) {
    return (mult(x, x, mod) + c) % mod;
}

__int128 binpower(__int128 base, __int128 e, __int128 mod) {
    __int128 result = 1;
    base %= mod;
    while (e) {
        if (e & 1) {
            result = (__int128)result * base % mod;
        }
        base = (__int128)base * base % mod;
        e >>= 1;
    }
    return result;
}

__int128 rho(__int128 n) {
    __int128 c = rand() % (n + 1);
    __int128 x = rand() % (n + 1);
    __int128 xx = x;
    long long g = 1;
    if (n % 2 == 0) {
        return 2;
    }

    while (g == 1) {
        x = f(x, c, n);
        xx = f(xx, c, n);
        xx = f(xx, c, n);
        long long diff = x - xx;
        if (diff < 0) {
            diff = -diff;
        }
        g = __gcd(diff, (long long)n);
    }
    return g;
}

bool check_composite(__int128 n, __int128 a, __int128 d, int s) {
    __int128 x = binpower(a, d, n);
    if (x == 1 || x == n - 1) {
        return false;
    }
    for (int r = 1; r < s; r++) {
        x = (__int128)x * x % n;
        if (x == n - 1) {
            return false;
        }
    }
    return true;
};


bool is_prime(__int128 n) {
    if (n < 2) {
        return false;
    }
    int r = 0;
    __int128 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for (int a : primes) {
        if (n == a) {
            return true;
        }
        if (check_composite(n, a, d, r)) {
            return false;
        }
    }
    return true;
}

void factor(__int128 n) {
    if (n == 1) {
        return;
    }
    if (is_prime(n)) {
        factors.insert(n);
        return;
    }

    __int128 divisor = rho(n);
    factor(divisor);
    factor(n / divisor);
    return;
}

int main() {
    IOS;
    for (int i = 1; i < K; i++) {
        modinv[i] = modPow(i, M - 2, M);
    }
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        long long n, k;
        cin >> n >> k;
        factor(n);
        int deg = k + 1;
        y[0] = 0;
        for (int i = 1; i <= deg; i++) {
            y[i] = (y[i - 1] + modPow(i, k, M)) % M;
        }
        long long tot = lagrange(n, k), bad = 0;
        vector<long long> f;
        for (auto it = factors.begin(); it != factors.end(); ++it) {
            f.push_back(*it);
        }
        int m = f.size(), bits = 1 << m;
        for (int j = 1; j < bits; j++) {
            long long prod = 1;
            for (int i = 0; i < m; i++) {
                int c = j & (1 << i);
                if (c != 0) {
                    prod *= f[i];
                }
            }
            long long sum = lagrange(n / prod, k) * modPow(prod % M, k, M) % M;
            if (__builtin_popcount(j) % 2 == 1) {
                bad = (bad + sum) % M;
            } else {
                bad = (bad - sum + M) % M;
            }
        }
        cout << (tot - bad + M) % M << endl;
        factors.clear();
    }

    return 0;
}
