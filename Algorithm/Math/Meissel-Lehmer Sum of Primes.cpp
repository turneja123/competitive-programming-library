#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 50;
const int M = 1000010;
const int P = 10000010;

int prime_cnt[P];
long long prime_sum[P];
long long dp[N][M];

vector<int> primes{0};
bitset<P> is_prime;
gp_hash_table<long long, __int128> mp;

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

__int128 phi(__int128 m, int n){
    if (n == 0) {
        return m * (m + 1) / 2;
    }
    if (m < M && n < N) {
        return dp[n][m];
    }
    if ((long long)primes[n] * primes[n] >= m && m < P) {
        return prime_sum[m] - prime_sum[primes[n]] + 1;
    }
    return phi(m, n - 1) - phi(udiv(m, primes[n]), n - 1) * primes[n];
}

__int128 lehmer(__int128 m){
    if (m < P) {
        return prime_sum[m];
    }
    auto it = mp.find(m);
    if (it != mp.end()) {
        return it->second;
    }
    int s = sqrt(0.5 + m), y = cbrt(0.5 + m);
    long long a = prime_cnt[y], b = prime_sum[y];

    __int128 res = phi(m, a) + b - 1;
    for (int i = a + 1; i <= prime_cnt[s]; i++) {
        res = res - (lehmer(udiv(m, primes[i])) - prime_sum[primes[i] - 1]) * primes[i];
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
        prime_sum[i] = prime_sum[i - 1] + (is_prime[i] ? i : 0);
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
}

int main() {
    IOS;
    sieve();
    for (int m = 0; m < M; m++) {
        dp[0][m] = (long long)m * (m + 1) / 2;
    }
    for (int n = 1; n < N; n++){
        for (int m = 1; m < M; m++){
            dp[n][m] = dp[n - 1][m] - dp[n - 1][udiv(m, primes[n])] * primes[n];
        }
    }
    __int128 ans = lehmer(1e12);
    print(ans);

    return 0;
}
