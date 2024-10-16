//https://www.spoj.com/problems/DIVCNTK/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int SQ = 1e6 + 5;
const int D = 1;

unsigned long long kk;

int deg, pos;
long long n, r;
bool composite[SQ];
int primes[SQ];
unsigned long long a[SQ];
unsigned long long poly[D];

unsigned long long pref[D][SQ];
unsigned long long g[D][SQ];

int block[2][SQ];

int get(long long x) {
    return x <= r ? block[0][x] : block[1][n / x];
}

void sieve(int n) {
    for (int i = 2; i < n; i++) {
        if (!composite[i]) {
            primes[++pos] = i;
            unsigned long long pw = 1;
            for (int k = 0; k < deg; k++) {
                pref[k][pos] = pref[k][pos - 1] + pw;
                pw = pw * i;
            }
            for (int j = 2 * i; j < n; j += i) {
                composite[j] = true;
            }
        }
    }
    return;
}

unsigned long long f(int p, int k) {
    return kk * k + 1;
}

unsigned long long calc(long long x, int j) {
    if (primes[j] >= x) {
        return 0;
    }
    int idx = get(x);
    unsigned long long ans = 0;
    for (int k = 0; k < deg; k++) {
        ans += poly[k] * g[k][idx];
    }
    for (int k = 0; k < deg; k++) {
        ans -= poly[k] * pref[k][j];
    }
    for (int i = j + 1; i <= pos && primes[i] <= x / primes[i]; i++) {
        long long pw = primes[i];
        for (int e = 1; pw <= x; e++) {
            ans += f(primes[i], e) * (calc(x / pw, i) + (e != 1));
            if (pw > x / primes[i]) {
                break;
            }
            pw *= primes[i];
        }
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> kk;
        deg = 1;
        poly[0] = kk + 1;

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
            for (int k = 0; k < deg; k++) {
                if (k == 0) {
                    g[k][tot] = x - 1;
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
                unsigned long long pw = 1;
                for (int k = 0; k < deg; k++) {
                    g[k][j] -= pw * (g[k][idx] - pref[k][i - 1]);
                    pw = pw * primes[i];
                }
            }
        }
        unsigned long long ans = (calc(n, 0) + 1);
        cout << ans << endl;
        pos = 0;
    }

    return 0;
}
