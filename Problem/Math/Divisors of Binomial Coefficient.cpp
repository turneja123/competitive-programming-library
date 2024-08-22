//https://atcoder.jp/contests/abc227/tasks/abc227_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int P = 1e6 + 5;
const long long M = 998244353;

vector<char> is_prime(P, false);
vector<long long> primes{2};

long long pw[P];

map<long long, long long> big;

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
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

void segmentedSieve(long long l, long long r) {
    if (l > r) {
        return;
    }
    vector<long long> seg(r - l + 1);
    for (long long i = 0; i < r - l + 1; i++) {
        seg[i] = l + i;
    }
    for (long long i : primes) {
        for (long long j = max(i * i, (l + i - 1) / i * i); j <= r; j += i) {
            while (seg[j - l] % i == 0) {
                seg[j - l] /= i;
            }
        }
    }

    for (long long i = 0; i < r - l + 1; i++) {
        if (seg[i] > P) {
            big[seg[i]]++;
        }
    }
    return;
}

int main() {
    IOS;
    is_prime[2] = true;
    for (int i = 3; i < P; i += 2) {
        is_prime[i] = true;
    }
    for (long long i = 3; i < P; i += 2){
        if (is_prime[i]) {
            primes.push_back(i);
        }
        for (long long j = i * i; is_prime[i] && j < P; j += (i << 1)){
            is_prime[j] = false;
        }
    }
    long long n, k;
    cin >> n >> k;
    if (n == k) {
        cout << 1;
        return 0;
    }
    segmentedSieve(max(n - k + 1, (long long)P), n);
    long long ans = 1;
    for (auto it = big.begin(); it != big.end(); ++it) {
        ans = ans * (it->second + 1) % M;
    }
    for (long long p : primes) {
        vector<long long> v;
        pw[p] = legendre(n, p) - legendre(k, p) - legendre(n - k, p);
    }
    for (long long p : primes) {
        ans = ans * (pw[p] + 1) % M;
    }
    cout << ans;
    return 0;
}
