//https://www.spoj.com/problems/MOON2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 1e6 + 5;
const long long M = 1e9 + 7;

long long y[K];
long long pref[K];
long long suf[K];
long long fact[K];
long long inv[K];
long long modinv[K];

int deg;

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

long long modInverse(long long a, long long m) {
    return modPow(a, M - 2, M);
}

long long lagrange(long long n, int r) {
    if (n <= deg) {
        return y[n];
    }
    pref[0] = n % M, suf[deg] = (n - deg) % M;
    for (int i = 1; i < deg; i++) {
        pref[i] = (pref[i - 1] * ((n - i) % M)) % M;
    }
    for (int i = deg - 1; i >= 0; i--) {
        suf[i] = (suf[i + 1] * ((n - i) % M)) % M;
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

long long binomial(long long n, long long k, long long m) {
    long long num = fact[n];
    long long denom = (inv[k] * inv[n - k]) % m;
    return num * denom % m;
}

long long calc(long long a, long long r, long long n) {
    long long c = 0;
    for (int i = 0; i <= deg; i++) {
        c = (c + (binomial(r + 1, i + 1, M) * modPow(M - a, r - i, M) % M) * y[i] % M) % M;
    }
    c = c * modInverse(modPow(M - a + 1, r + 1, M), M) % M;
    long long cur = 1;
    for (int i = 0; i <= deg; i++) {
        y[i] = ((y[i] - c + M) % M) * cur % M;
        cur = cur * modInverse(a, M) % M;
    }
    return (lagrange(n, r) * modPow(a, n, M) + c + M) % M;
}

int main() {
    IOS;
    for (int i = 1; i < K; i++) {
        modinv[i] = modPow(i, M - 2, M);
    }
    fact[0] = 1;
    inv[0] = 1;
    for (int i = 1; i < K; i++) {
        inv[i] = (inv[i - 1] * modinv[i]) % M;
        fact[i] = (fact[i - 1] * i) % M;
    }
    int t;
    cin >> t;
    while (t--) {
        long long a, r, n;
        cin >> n >> a >> r;
        if (a == 1) {
            deg = r + 1;
        } else {
            deg = r;
        }
        y[0] = modPow(0, r, M);
        long long pw = a;
        for (int i = 1; i <= deg; i++) {
            y[i] = (y[i - 1] + pw * modPow(i, r, M)) % M;
            pw = (pw * a) % M;
        }
        long long ans = 0;
        if (a == 1) {
            ans = lagrange(n, r);
        } else {
            ans = calc(a, r, n);
        }
        cout << ans << endl;
    }
    return 0;
}
