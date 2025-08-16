//https://www.spoj.com/problems/MOON4/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 1e8 + 5;
const long long M = 1e9 + 7;

int y[K];
int suf[K];
int fact[K];
int inv[K];
int modinv[K];

int deg;

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

long long modInverse(ll a) {
    return modPow(a, M - 2);
}


long long lagrange(long long n, int r) {
    if (n <= deg) {
        return y[n];
    }
    int pref = 1;
    suf[deg] = (n - deg) % M;
    for (int i = deg - 1; i >= 0; i--) {
        suf[i] = ((ll)suf[i + 1] * ((n - i) % M)) % M;
    }
    long long ans = 0;
    for (int i = 0; i <= deg; i++) {
        long long num, denom;
        if (i == 0) {
            num = suf[1];
        } else if (i == deg) {
            num = pref;
        } else {
            num = (ll)pref * suf[i + 1] % M;
        }
        denom = (ll)inv[i] * inv[deg - i] % M;
        pref = (ll)pref * ((n - i) % M) % M;
        if ((deg - i) % 2 == 0) {
            ans = (ans + (((ll)y[i] * num % M) * denom) % M) % M;
        } else {
            ans = (ans - (((ll)y[i] * num % M) * denom) % M + M) % M;
        }
    }
    return ans;
}

long long binomial(long long n, long long k, long long m) {
    long long num = fact[n];
    long long denom = ((ll)inv[k] * inv[n - k]) % m;
    return num * denom % m;
}

long long calc(long long a, long long r, long long n) {
    long long c = 0;
    ll b = (M - a) % M, ib = modInverse(b), pb = modPow(b, r);
    ll C = (r + 1) % M;
    for (int i = 0; i <= deg; ++i) {
        c = (c + C * pb % M * y[i]) % M;
        C = C * (r + 1 - (i + 1)) % M * modinv[i + 2] % M;
        pb = pb * ib % M;
    }
    c = c * modInverse(modPow(M - a + 1, r + 1)) % M;
    long long cur = 1;
    ll inv = modInverse(a);
    for (int i = 0; i <= deg; i++) {
        y[i] = (((ll)y[i] - c + M) % M) * cur % M;
        cur = cur * inv % M;
    }
    return (lagrange(n, r) * modPow(a, n) + c + M) % M;
}

int main() {
    IOS;
    for (int i = 1; i < K; i++) {
        modinv[i] = (i == 1 ? 1 : M - (M / i) * modinv[M % i] % M);
    }
    fact[0] = 1;
    inv[0] = 1;
    for (int i = 1; i < K; i++) {
        inv[i] = ((ll)inv[i - 1] * modinv[i]) % M;
        fact[i] = ((ll)fact[i - 1] * i) % M;
    }
    /*inv[K - 1] = modInverse(fact[K - 1]);
    for (int i = K - 2; i >= 1; i--) {
        inv[i] = (ll)inv[i + 1] * (i + 1) % M;
    }*/
    int t;
    cin >> t;
    while (t--) {
        long long a, r, n;
        cin >> n >> a >> r;
        a %= M;
        if (a == 1) {
            deg = r + 1;
        } else {
            deg = r;
        }
        if (a == 1) {
            deg = r + 1;
        } else {
            deg = r;
        }
        y[0] = modPow(0, r);
        int pw = a;
        for (int i = 1; i <= deg; i++) {
            y[i] = (y[i - 1] + (ll)pw * modPow(i, r)) % M;
            pw = ((ll)pw * a) % M;
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
