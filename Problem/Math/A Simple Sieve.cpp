//https://www.spoj.com/problems/ASSIEVE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 998244353;
const int SQ = 2e5 + 5;
const int K = 1e3 + 5;

int pos, deg;
ll n, r, k;
int x[4][4];
bool composite[SQ];
int primes[SQ];
ll pk[SQ];
ll a[SQ];

ll pref[SQ][4];
ll g[SQ][4];
ll sum[SQ][4];
ll cnt[SQ][2];

int block[2][SQ];

ll y[K];
ll c[2][K];
ll fact[K];

ll modPow(ll a, ll y) {
    ll res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

int get(ll x) {
    return x <= r ? block[0][x] : block[1][n / x];
}

void sieve(int n) {
    for (int i = 2; i < n; i++) {
        if (!composite[i]) {
            primes[++pos] = i;
            pk[pos] = modPow(i, k);
            for (int t = 0; t < 4; t++) {
                pref[pos][t] = pref[pos - 1][t];
            }
            pref[pos][i % 4] = (pref[pos][i % 4] + pk[pos]) % M;
            for (int j = 2 * i; j < n; j += i) {
                composite[j] = true;
            }
        }
    }
    return;
}

int main() {
    IOS;
    cin >> n >> k;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> x[i][j];
        }
    }
    r = sqrt(n);
    sieve(r + 1);
    for (int i = 1; i <= r; i++) {
        for (int t = 0; t < 4; t++) {
            sum[i][t] = sum[i - 1][t];
        }
        sum[i][i % 4] = (sum[i][i % 4] + modPow(i, k)) % M;
    }
    deg = k + 1;
    fact[0] = 1;
    for (int i = 1; i <= deg; i++) {
        fact[i] = fact[i - 1] * i % M;
    }
    for (int z = 0; z < 2; z++) {
        y[0] = 0;
        for (int i = 1; i <= deg; i++) {
            y[i] = (y[i - 1] + modPow(4 * (i - 1) + 2 * z + 1, k)) % M;
        }
        for (int s = 0; s <= deg; s++) {
            c[z][s] = y[0] * modPow(fact[s], M - 2) % M;
            for (int i = 0; i + s < deg; i++) {
                y[i] = (y[i + 1] - y[i] + M) % M;
            }
        }
    }
    int tot = 0, big = 0;
    ll two = modPow(2, k);
    ll i = 1;
    while (i <= n) {
        ll v = n / i;
        a[++tot] = v;
        g[tot][2] = (v >= 2 ? two : 0);
        if (v <= r) {
            g[tot][1] = (sum[v][1] - 1 + M) % M;
            g[tot][3] = sum[v][3];
            block[0][v] = tot;
        } else {
            big = tot;
            cnt[tot][0] = (v + 3) / 4 % M;
            cnt[tot][1] = (v + 1) / 4 % M;
            block[1][n / v] = tot;
        }
        i = n / v + 1;
    }
    for (int j = 1; j <= big; j++) {
        g[j][1] = c[0][deg];
        g[j][3] = c[1][deg];
    }
    for (int s = deg - 1; s >= 0; s--) {
        for (int j = 1; j <= big; j++) {
            g[j][1] = ((unsigned ll)g[j][1] * (cnt[j][0] + M - s) + c[0][s]) % M;
            g[j][3] = ((unsigned ll)g[j][3] * (cnt[j][1] + M - s) + c[1][s]) % M;
        }
    }
    for (int j = 1; j <= big; j++) {
        g[j][1] = (g[j][1] - 1 + M) % M;
    }
    for (int i = 2; i <= pos; i++) {
        ll p = primes[i];
        for (int j = 1; j <= tot && p * p <= a[j]; j++) {
            int idx = get(a[j] / p);
            for (int t = 1; t < 4; t += 2) {
                int u = t * p % 4;
                g[j][t] = (g[j][t] - pk[i] * (g[idx][u] - pref[i - 1][u] + M) % M + M) % M;
            }
        }
    }
    for (int i = pos; i >= 1; i--) {
        ll p = primes[i];
        for (int j = 1; j <= tot && p * p <= a[j]; j++) {
            ll pe = p, pw = pk[i];
            for (int e = 1; pe * p <= a[j]; e++) {
                int idx = get(a[j] / pe), cl = p * e % 4;
                for (int t = 0; t < 4; t++) {
                    g[j][x[cl][t]] = (g[j][x[cl][t]] + pw * (g[idx][t] - pref[i][t] + M)) % M;
                }
                pe *= p;
                pw = pw * pk[i] % M;
                cl = p * (e + 1) % 4;
                g[j][cl] = (g[j][cl] + pw) % M;
            }
        }
    }
    for (int i = 1; i <= r; i++) {
        int idx = get(n / i);
        for (int t = 0; t < 4; t++) {
            cout << (g[idx][t] + (t == 0)) % M << (t == 3 ? endl : " ");
        }
    }
    return 0;
}
