//https://codeforces.com/contest/2081/problem/G2
#pragma GCC optimize("Ofast,unroll-loops")
#include <iterator>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using u32 = unsigned int;
using u64 = unsigned long long;

const int SQ = 5e6 + 5;
const int D = 2;

int deg, pos;
long long n, r;
bool composite[SQ];
int primes[SQ];
long long p_pow[SQ];
int pi[SQ];
long long a[SQ];

u32 pref[D][SQ];
u32 g[D][SQ];

int block[2][SQ];

inline int get(long long x) {
    return x <= r ? block[0][x] : block[1][n / x];
}

void sieve(int n) {
    for (int i = 2; i < n; i++) {
        pi[i] = pi[i - 1];
        if (!composite[i]) {
            primes[++pos] = i;
            p_pow[pos] = (long long)i * i;
            pi[i] = pos;
            u32 pw = 1;
            for (int k = 0; k < deg; k++) {
                pref[k][pos] = pref[k][pos - 1] + pw;
                pw = pw * i;
            }
            if ((long long)i * i < n) {
                for (long long j = (long long)i * i; j < n; j += i) {
                    composite[j] = true;
                }
            }
        }
    }
    return;
}

u32 f(int p, long long pw) {
    return (u32)(pw / p) * (p - 1);
}

u32 sum(long long x, int j) {
    if (x < SQ) {
        int idx = pi[x];
        return pref[1][idx] - pref[1][j] - (pref[0][idx] - pref[0][j]);
    }
    int idx = get(x);
    return g[1][idx] - pref[1][j] - (g[0][idx] - pref[0][j]);
}

u32 val(long long x, int j, u64 A, u64 B, u64 c, u64 rem) {
    u32 ans = 0;
    u64 s;
    ans += (u32)c * sum(x, j);
    if (j == 0) {
        s = 2 * A / B;
    } else {
        u64 p = primes[j], u = rem * p + A, v = p * B;
        if (u < v) {
            return ans;
        }
        s = c + u / v;
    }
    for (u64 t = c + 1; t <= s; t++) {
        long long y = min((u64)x, t * B / (t * B - A));
        ans += sum(y, j);
    }
    return ans;
}

u32 calc(long long x, int j, u64 A, u64 B, u64 C, u64 R) {
    if (primes[j] >= x) {
        return 0;
    }
    u32 ans = val(x, j, A, B, C, R);
    for (int i = j + 1; i <= pos; i++) {
        long long p = primes[i];
        if (p_pow[i] > x) {
            break;
        }
        long long pw = p, lim = x / p;
        u64 ap = A * p, bp = B * (p - 1), c = ap / bp, rem = ap - c * bp;
        int ok = rem * p + ap < p * bp;
        u32 ph = p - 1;
        long long y = x / p;
        if (i < pos && p_pow[i + 1] > y) {
            if (ok) {
                ans += ph * (u32)c * sum(y, i);
            } else {
                ans += ph * val(y, i, ap, bp, c, rem);
            }
        } else {
            ans += ph * calc(y, i, ap, bp, c, rem);
        }
        while (pw <= lim) {
            pw *= p;
            ph *= p;
            ans += ph * (u32)c;
            if (pw <= lim) {
                y = x / pw;
                if (i < pos && p_pow[i + 1] > y) {
                    if (ok) {
                        ans += ph * (u32)c * sum(y, i);
                    } else {
                        ans += ph * val(y, i, ap, bp, c, rem);
                    }
                } else {
                    ans += ph * calc(y, i, ap, bp, c, rem);
                }
            }
        }
    }
    return ans;
}

int main() {
    IOS;
    deg = 2;
    cin >> n;
    r = sqrt(n);
    while ((long long)r * r < n) {
        ++r;
    }
    while ((long long)r * r > n) {
        --r;
    }
    sieve(SQ);
    int tot = 0;
    long long i = 1;
    while (i <= n) {
        long long x = n / i;
        a[++tot] = x;
        u32 z = x;
        for (int k = 0; k < deg; k++) {
            if (k == 0) {
                g[k][tot] = z - 1;
            }
            if (k == 1) {
                g[k][tot] = (u32)((__uint128_t)x * (x + 1) / 2 - 1);
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
        long long p = primes[i];
        if (p_pow[i] > n) {
            break;
        }
        for (int j = 1; j <= tot && p_pow[i] <= a[j]; j++) {
            int idx = get(a[j] / primes[i]);
            g[0][j] = g[0][j] - (g[0][idx] - pref[0][i - 1]);
            g[1][j] = g[1][j] - primes[i] * (g[1][idx] - pref[1][i - 1]);
        }
    }
    u32 ans = (u32)((__uint128_t)n * (n + 1) / 2) - (calc(n, 0, 1, 1, 1, 0) + 1);
    cout << ans;
    return 0;
}
