//https://www.spoj.com/problems/DIVFACT4/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 100;
const int M = 100010;
const int P = 10000010;

int prime_cnt[P];
long long dp[N][M];

vector<int> primes;
bitset<P> is_prime;
gp_hash_table<long long, long long> mp;

long long phi(long long m, int n){
    if (n == 0) {
        return m;
    }
    if (m < M && n < N) {
        return dp[n][m];
    }
    if ((long long)primes[n - 1] * primes[n - 1] >= m && m < P) {
        return prime_cnt[m] - n + 1;
    }
    return phi(m, n - 1) - phi(m / primes[n - 1], n - 1);
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
    for (int i = a; primes[i] <= s; i++) {
        res = res - lehmer(m / primes[i]) + lehmer(primes[i]) - 1;
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
}

__int128 modPow(__int128 x, __int128 y, __int128 m) {
    if (x == 0 && y == 0) {
        return 1;
    }
    __int128 res = 1;
    x = x % m;
    if (x == 0) {
        return 0;
    }
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % m;
        }
        y >>= 1;
        x = (x * x) % m;
    }
    return res;
}

long long legendre(long long n, long long k) {
    long long fact_pow = 0;
    while (n) {
        n /= k;
        fact_pow += n;
    }
    return fact_pow;
}

int main() {
    IOS;
    sieve();
    for (int m = 0; m < M; m++) {
        dp[0][m] = m;
    }
    for (int n = 1; n < N; n++){
        for (int m = 0; m < M; m++){
            dp[n][m] = dp[n - 1][m] - dp[n - 1][m / primes[n - 1]];
        }
    }
    int t;
    cin >> t;
    while (t--) {
        long long n, mm;
        cin >> n >> mm;
        __int128 ans = 1, m = mm;
        if (m == 1) {
            cout << 0 << endl;
            continue;
        }
        if (n <= 1e4) {
            for (int i = 2; i <= n; i++) {
                if (is_prime[i]) {
                    ans = (ans * (__int128)(legendre(n, i) + 1)) % m;
                }
            }
            long long llans = ans;
            cout << llans << endl;
            continue;
        }
        for (long long i = 1; i < sqrt(n); i++) {
            if (legendre(n, n / i) != i) {
                continue;
            }
            ans = (ans * modPow((i + 1), lehmer(n / i) - lehmer(n / (i + 1)), m)) % m;
        }
        for (int i = 2; i < n; i++) {
            long long fact_pow = legendre(n, i);
            if (fact_pow < sqrt(n)) {
                break;
            }
            if (is_prime[i]) {
                ans = (ans * (fact_pow + 1)) % m;
            }
        }
        long long llans = ans;
        cout << llans << endl;
    }
    return 0;
}
