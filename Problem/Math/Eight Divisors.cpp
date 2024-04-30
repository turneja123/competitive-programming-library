//https://projecteuler.net/problem=501
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

int main() {
    //IOS;
    sieve();
    for (int m = 0; m < M; m++) {
        dp[0][m] = m;
    }
    for (int n = 1; n < N; n++){
        for (int m = 0; m < M; m++){
            dp[n][m] = dp[n - 1][m] - dp[n - 1][m / primes[n - 1]];
        }
    }
    long long n = 1e12;
    long long ans = 0;
    for (long long i = 2; i < sqrt(n); i++) {
        long long k = i * i * i;
        if (n / k < i) {
            break;
        }
        if (is_prime[i]) {
            ans += lehmer(n / k) - lehmer(i);
        }
    }
    for (long long i = 2; i < sqrt(n); i++) {
        if (cbrt(n / i) < i) {
            break;
        }
        if (is_prime[i]) {
            ans += lehmer(cbrt(n / i)) - lehmer(i);
        }
    }
    for (long long i = 2; i < sqrt(n); i++) {
        if (!is_prime[i]) {
            continue;
        }
        for (long long j = i + 1; j < sqrt(n); j++) {
            if (!is_prime[j]) {
                continue;
            }
            long long k = i * j;
            if (n / k < j) {
                break;
            }
            ans += lehmer(n / k) - lehmer(j);
        }
    }
    for (long long i = 2; i < n; i++) {
        long long k = i * i * i * i * i * i * i;
        if (k > n) {
            break;
        }
        if (is_prime[i]) {
            ans++;
        }
    }
    cout << ans;
    return 0;
}
