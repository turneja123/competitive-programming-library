//https://www.spoj.com/problems/TAHSINREC/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e5 + 5;

bool is_prime[N];
int ct[N];

vector<int> primes{2};

long long legendre(long long n, long long k) {
    long long fact_pow = 0;
    while (n) {
        n /= k;
        fact_pow += n;
    }
    return fact_pow;
}

long long modPow(long long base, long long e, long long mod) {
    long long result = 1;
    base %= mod;
    while (e) {
        if (e & 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        e >>= 1;
    }
    return result;
}

void fact(int n, int sgn) {
    for (int p : primes) {
        if (p > n) {
            break;
        }
        ct[p] += legendre(n, p) * sgn;
    }
    return;
}

int main() {
    IOS;
    is_prime[2] = true;
    for (int i = 3; i < N; i += 2) {
        is_prime[i] = true;
    }
    for (int i = 3; i < N; i += 2) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < N; j += i) {
                is_prime[j] = false;
            }
            primes.push_back(i);
        }
    }
    int t;
    cin >> t;
    while (t--) {
        long long n, k, m;
        cin >> n >> k >> m;
        if (n < k) {
            cout << 0 << endl;
            continue;
        }
        fact(n, 1);
        fact(k, -1);
        fact(n - k, -1);
        long long ans = 1;
        for (int p : primes) {
            ans = (__int128)ans * modPow(p, ct[p], m) % m;
            ct[p] = 0;
        }
        cout << ans << endl;

    }

    return 0;
}
