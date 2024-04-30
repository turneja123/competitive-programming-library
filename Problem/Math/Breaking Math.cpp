//https://www.spoj.com/problems/BBAD/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 66;
const int M = 510510;
const int P = 5000010;
const int V = 7;
const int R = 4e4;

int prime_cnt[P];
long long dp[N][M];

vector<int> primes;
vector<char> is_prime(P, false);
gp_hash_table<long long, long long> mp;
long long w[11];
long long a[11];
int prod[V];
long long n; int d, ind;
long long powers[R][32];

void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

auto udiv = [](const uint64_t& a, const uint32_t& b) -> uint64_t {
    return (double)a / b + 1e-9;
};

long long phi(long long m, int n){
    if (n == 0) {
        return m;
    }
    if (m < M && n < N) {
        return dp[n][m];
    }
    if (n < V) {
        return dp[n][m % prod[n - 1]] + udiv(m, prod[n - 1]) * dp[n][prod[n - 1]];
    }
    long long p = primes[n - 1];
    if (m < P && p * p >= m) {
        return prime_cnt[m] - n + 1;
    }
    if (p * p * p < m || m >= M) {
        return phi(m, n - 1) - phi(udiv(m, p), n - 1);
    }

    int lim = prime_cnt[(int)sqrt(0.5 + m)];
    uint64_t res = prime_cnt[m] - (lim + n - 2) * (lim - n + 1) / 2;
    for (int i = n; i < lim; i++){
        res += prime_cnt[udiv(m, primes[i])];
    }

    return res;
}

long long lehmer(long long m){
    if (m < P) {
        return prime_cnt[m];
    }
    if (mp.find(m) != mp.end()) {
        return mp[m];
    }

    int s = sqrt(0.5 + m), y = cbrt(0.5 + m);
    int a = prime_cnt[y];

    long long res = phi(m, a) + a - 1;
    for (int i = a; i < prime_cnt[s]; i++) {
        res -= lehmer(udiv(m, primes[i])) - i;
    }
    return mp[m] = res;
}

void sieve(){
    is_prime[2] = true;
    for (int i = 3; i < P; i += 2) {
        is_prime[i] = true;
    }
    for (int i = 3; i * i < P; i += 2){
        for (int j = i * i; is_prime[i] && j < P; j += (i << 1)){
            is_prime[j] = false;
        }
    }
    for (int i = 1; i < P; i++){
        prime_cnt[i] = prime_cnt[i - 1] + is_prime[i];
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    prod[0] = primes[0];
    for (int i = 1; i < V; i++) {
        prod[i] = prod[i - 1] * primes[i];
    }
}

__int128 smallpw(__int128 x, int k, bool fl = true) {
    __int128 res = 1;
    for (int i = 1; i <= k; i++) {
        res *= x;
        if (res > n && fl) {
            return -1;
        }
    }
    return res;
}

void calc(long long prod, int i) {
    if (i == d - 1) {
        w[d] += lehmer(n / prod) - prime_cnt[a[d - 2]];
        __int128 mn = (__int128)prod * primes[ind + 1] * primes[ind + 1];
        if (mn <= n) {
            for (int pw = 2; pw < 30; pw++) {
                int l = ind + 1, r = R, ans = ind;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    __int128 targ = powers[mid][pw];
                    if (targ == -1) {
                        r = mid - 1;
                        continue;
                    }
                    __int128 lim = (__int128)prod * targ;
                    if (lim <= n) {
                        l = mid + 1;
                        ans = mid;
                    } else {
                        r = mid - 1;
                    }
                }
                w[d] += ans - ind;
                mn *= (__int128)primes[ind + 1];
                if (mn > n) {
                    break;
                }
            }
        }
        return;
    }
    while (n > prod * a[d - 2]) {
        calc(prod, i + 1);
        prod *= a[i];
    }
}

int main() {
    IOS;
    sieve();
    for (int m = 0; m < M; m++) {
        dp[0][m] = m;
    }
    for (int n = 1; n < N; n++){
        for (int m = 0; m < M; m++){
            dp[n][m] = dp[n - 1][m] - dp[n - 1][udiv(m, primes[n - 1])];
        }
    }
    for (int i = 0; i < R; i++) {
        long long pw = primes[i];
        for (int j = 2; j < 32; j++) {
            if (pw == -1) {
                powers[i][j] = -1;
                continue;
            }
            pw *= primes[i];
            if (pw > (long long)1e11) {
                pw = -1;
                powers[i][j] = -1;
            } else {
                powers[i][j] = pw;
            }
        }
    }
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        long long base;
        cin >> n >> base;
        for (int i = 0; i <= 10; i++) {
            w[i] = 0;
        }
        w[0] = 1;
        w[1] = lehmer(n) - lehmer(sqrt(n));
        for (int ip = 0; ip < primes.size(); ip++) {
            long long i = primes[ip];
            if (i > sqrt(n)) {
                break;
            }
            long long k = i;
            while (k <= n) {
                w[1]++;
                k *= i;
            }
        }
        for (int ip = 0; ip < primes.size(); ip++) {
            long long i = primes[ip];
            if (i >= udiv(n, i)) {
                break;
            }
            a[0] = i, d = 2, ind = ip;
            calc(i, 0); long long prod = i;
            for (int jp = ip + 1; jp < primes.size(); jp++) {
                long long j = primes[jp];
                if (j >= n / (i * j)) {
                    break;
                }
                a[1] = j, d = 3, ind = jp;
                calc(i * j, 0);
                for (int pp = jp + 1; pp < primes.size(); pp++) {
                    long long p = primes[pp];
                    if (p >= n / (i * j * p)) {
                        break;
                    }
                    a[2] = p, d = 4, ind = pp;
                    calc(i * j * p, 0);
                    for (int xp = pp + 1; xp < primes.size(); xp++) {
                        long long x = primes[xp];
                        if (x >= n / (i * j * p * x)) {
                            break;
                        }
                        a[3] = x, d = 5, ind = xp;
                        calc(i * j * p * x, 0);
                        for (int yp = xp + 1; yp < primes.size(); yp++) {
                            long long y = primes[yp];
                            if (y >= n / (i * j * p * x * y)) {
                                break;
                            }
                            a[4] = y, d = 6, ind = yp;
                           // calc(i * j * p * x * y, 0);
                            for (int zp = yp + 1; zp < primes.size(); zp++) {
                                long long z = primes[zp];
                                if (z >= n / (i * j * p * x * y * z)) {
                                    break;
                                }
                                a[5] = z, d = 7, ind = zp;
                                calc(i * j * p * x * y * z, 0);
                                for (int qp = zp + 1; qp < primes.size(); qp++) {
                                    long long q = primes[qp];
                                    if (q >= n / (i * j * p * x * y * z * q)) {
                                        break;
                                    }
                                    a[6] = q, d = 8, ind = qp;
                                    calc(i * j * p * x * y * z * q, 0);
                                    for (int rp = qp + 1; rp < primes.size(); rp++) {
                                        long long r = primes[rp];
                                        if (r >= n / (i * j * p * x * y * z * q * r)) {
                                            break;
                                        }
                                        a[7] = r, d = 9, ind = rp;
                                        calc(i * j * p * x * y * z * q * r, 0);
                                        for (int fp = rp + 1; fp < primes.size(); fp++) {
                                            long long f = primes[fp];
                                            if (f >= n / (i * j * p * x * y * z * q * r * f)) {
                                                break;
                                            }
                                            a[8] = f, d = 10, ind = fp;
                                            calc(i * j * p * x * y * z * q * r * f, 0);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        long long chk = 0, ans = 0;
        for (int i = 0; i <= 10; i++) {
            chk += w[i];
        }
        w[6] = n - chk;
        for (int i = 0; i <= 10; i++) {
            ans += w[i] * smallpw(base, i, false);
        }
        //assert(chk == n);
        cout << "Case " << tt << ": " << ans << endl;
    }


    return 0;
}
