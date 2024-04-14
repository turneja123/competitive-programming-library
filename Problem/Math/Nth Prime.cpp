//https://www.spoj.com/problems/NTHPRIME/
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

    int s = sqrt(0.5 + m), y = cbrt(0.5 + m);
    int a = prime_cnt[y];

    long long res = phi(m, a) + a - 1;
    for (int i = a; primes[i] <= s; i++) {
        res = res - lehmer(m / primes[i]) + lehmer(primes[i]) - 1;
    }
    return res;
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
    long long n;
    cin >> n;
    long long l = (n < 1000) ? n : n * (log(n) / 2), r = (n < 1000) ? n * 50 : n * (log(n) * 2), ans = r;
    while (l <= r) {
        long long mid = (l + r) / 2;
        long long p = lehmer(mid);
        if (p >= n) {
            if (p == n) {
                ans = min(ans, mid);
            }
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans;
    return 0;
}
