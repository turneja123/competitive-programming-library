//https://www.spoj.com/problems/KDIV/
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
const int G = 5041;

int prime_cnt[P];
long long dp[N][M];
bool gcd_table[R];

vector<int> primes;
vector<char> is_prime(P, false);
gp_hash_table<long long, long long> mp;
long long a[11];
int prod[V];
long long n, k; int d, ind;
long long powers[R][32];
vector<long long> D;

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

void calc(long long prod, long long divs, int i) {
    if (divs * 2 > k || !gcd_table[divs]) {
        return;
    }

    if (i == d - 1) {
        D[divs * 2] += lehmer(udiv(n, prod)) - prime_cnt[a[d - 2]];
        __int128 mn = (__int128)prod * primes[ind + 1] * primes[ind + 1];
        if (mn <= n) {
            for (int pw = 2; pw < 30; pw++) {
                if (divs * (pw + 1) != k) {
                    mn *= (__int128)primes[ind + 1];
                    if (mn > n) {
                        break;
                    }
                    continue;
                }
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
                D[divs * (pw + 1)] += ans - ind;
                mn *= (__int128)primes[ind + 1];
                if (mn > n) {
                    break;
                }
            }
        }
        return;
    }
    long long j = 2;
    while (n > prod * a[d - 2]) {
        calc(prod, divs * j, i + 1);
        j++;
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
            if (pw == -1 && i != 0) {
                powers[i][j] = -1;
                continue;
            }
            pw *= primes[i];
            if (pw > (long long)1e11 && i != 0) {
                pw = -1;
                powers[i][j] = -1;
            } else {
                powers[i][j] = pw;
            }
        }
    }
    powers[0][0] = 1, powers[0][1] = 2;
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        long long l, r;
        cin >> l >> r >> k; l--;
        if (k < R) {
            for (int i = 1; i < R; i++) {
                if (k % i == 0) {
                    gcd_table[i] = true;
                } else {
                    gcd_table[i] = false;
                }
            }
        }
        long long ans = 0;
        for (int cs = 1; cs <= 2; cs++) {
            if (k >= R) {
                continue;
            }
            D.clear(); D.resize(R, 0);
            n = (cs == 1) ? l : r;
            if (n == 0) {
                continue;
            }
            D[1] = 1;
            D[2] = lehmer(n) - lehmer(sqrt(n));
            for (int ip = 0; ip < primes.size(); ip++) {
                long long i = primes[ip];
                if (i > sqrt(n)) {
                    break;
                }
                long long k = i, j = 2;
                while (k <= n) {
                    D[j++]++;
                    k *= i;
                }
            }
            for (int ip = 0; ip < primes.size(); ip++) {
                long long i = primes[ip];
                if (i * i >= n) {
                    break;
                }
                a[0] = i, d = 2, ind = ip;
                calc(i, 1, 0);
                for (int jp = ip + 1; jp < primes.size(); jp++) {
                    long long j = primes[jp];
                    if (j * i * j >= n) {
                        break;
                    }
                    a[1] = j, d = 3, ind = jp;
                    calc(i * j, 1, 0);
                    for (int pp = jp + 1; pp < primes.size(); pp++) {
                        long long p = primes[pp];
                        if (p * i * j * p >= n) {
                            break;
                        }
                        a[2] = p, d = 4, ind = pp;
                        calc(i * j * p, 1, 0);
                        for (int xp = pp + 1; xp < primes.size(); xp++) {
                            long long x = primes[xp];
                            if (x * i * j * p * x >= n) {
                                break;
                            }
                            a[3] = x, d = 5, ind = xp;
                            calc(i * j * p * x, 1, 0);
                            for (int yp = xp + 1; yp < primes.size(); yp++) {
                                long long y = primes[yp];
                                if (y * i * j * p * x * y >= n) {
                                    break;
                                }
                                a[4] = y, d = 6, ind = yp;
                                calc(i * j * p * x * y, 1, 0);
                                for (int zp = yp + 1; zp < primes.size(); zp++) {
                                    long long z = primes[zp];
                                    if (z * i * j * p * x * y * z >= n) {
                                        break;
                                    }
                                    a[5] = z, d = 7, ind = zp;
                                    calc(i * j * p * x * y * z, 1, 0);
                                    for (int qp = zp + 1; qp < primes.size(); qp++) {
                                        long long q = primes[qp];
                                        if (q * i * j * p * x * y * z * q >= n) {
                                            break;
                                        }
                                        a[6] = q, d = 8, ind = qp;
                                        calc(i * j * p * x * y * z * q, 1, 0);
                                        for (int rp = qp + 1; rp < primes.size(); rp++) {
                                            long long r = primes[rp];
                                            if (r * i * j * p * x * y * z * q * r >= n) {
                                                break;
                                            }
                                            a[7] = r, d = 9, ind = rp;
                                            calc(i * j * p * x * y * z * q * r, 1, 0);
                                            for (int fp = rp + 1; fp < primes.size(); fp++) {
                                                long long f = primes[fp];
                                                if (f * i * j * p * x * y * z * q * r * f >= n) {
                                                    break;
                                                }
                                                a[8] = f, d = 10, ind = fp;
                                                calc(i * j * p * x * y * z * q * r * f, 1, 0);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (cs == 1) {
                ans -= D[k];
            } else {
                ans += D[k];
            }
        }
        cout << "Case " << tt << ": " << ans << endl;
    }
    return 0;
}
