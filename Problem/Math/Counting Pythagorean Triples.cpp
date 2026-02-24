//https://www.spoj.com/problems/PYTRIP3/
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int SQT = 2500005;
const int SQP = 1200005;

long long n, r;

unsigned char composite[SQP];
int primes[SQP], pos;

int pref0[SQP], pref1[SQP];
unsigned char is1[SQP];

long long a[SQT];
long long g0[SQT], g1[SQT];

int block0[SQP], block1[SQP];

static inline int get(long long x) { return x <= r ? block0[x] : block1[n / x]; }
auto udiv = [](const uint64_t& a, const uint64_t& b) -> uint64_t {
    return (double)a / b + 1e-9;
};

void sieve(int n) {
    for (int i = 2; i < n; i++) if (!composite[i]) {
        primes[++pos] = i;
        pref0[pos] = pref0[pos - 1] + ((i & 3) == 1);
        pref1[pos] = pref1[pos - 1] + ((i & 3) == 3);
        if ((ll)i * i < n) for (ll j = (ll)i * i; j < n; j += i) composite[(int)j] = 1;
    }
}

ll calc(long long x, int j) {
    if (primes[j] >= x) return 0;
    int idx = get(x);
    ll ans = 3 * g0[idx] + g1[idx] - 3 * (ll)pref0[j] - (ll)pref1[j] + (x >= 2) - (j >= 1);

    for (int i = j + 1; i <= pos && (ll)primes[i] * primes[i] <= x; i++) {
        ll p = primes[i], pw = p, lim = udiv(x, p);
        for (int e = 1; pw <= x; e++) {
            ans += (is1[i] ? 2LL * e + 1 : 1LL) * (calc(udiv(x, pw), i) + (e != 1));
            if (pw * p > x) break;
            pw *= p;
        }
    }
    return ans;
}

int main() {
    IOS;
    cin >> n;

    r = sqrtl((long double)n);
    while (r * r < n) ++r;
    while (r * r > n) --r;

    sieve((int)r + 1);
    for (int i = 1; i <= pos; i++) is1[i] = ((primes[i] & 3) == 1);

    int tot = 0;
    for (long long i = 1; i <= n; ) {
        long long x = n / i;
        a[++tot] = x;
        g0[tot] = (x - 1) / 4;
        g1[tot] = (x + 1) / 4;
        if (x <= r) block0[x] = tot;
        else block1[n / x] = tot;
        i = n / x + 1;
    }

    for (int i = 2; i <= pos; i++) {
        int p = primes[i], p1 = ((p & 3) == 1);
        int P0 = pref0[i - 1], P1 = pref1[i - 1];
        for (int j = 1; j <= tot && (ll)p * p <= a[j]; j++) {
            long long t = a[j] / p;
            int idx = (t <= r ? block0[t] : block1[n / t]);
            long long u0 = g0[idx] - P0, u1 = g1[idx] - P1;
            if (p1) g0[j] -= u0, g1[j] -= u1;
            else g0[j] -= u1, g1[j] -= u0;
        }
    }

    cout << (calc(n, 0) + 1 - n) / 2;
    return 0;
}
