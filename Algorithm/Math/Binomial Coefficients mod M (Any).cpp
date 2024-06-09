//https://www.codechef.com/problems/SANDWICH
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;
const int N = 1e6 + 5;

int spf[N];
bool is_prime[N];

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

long long modPow(long long a, long long y, const long long M) {
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

long long extendedEuclidean(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    long long x1, y1;
    long long d = extendedEuclidean(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

long long modInverse(long long a, long long M) {
    long long x, y;
    long long g = extendedEuclidean(a, M, x, y);
    if (g != 1) {
        return -1;
    }
    return (x % M + M) % M;
}

long long factMod(long long n, int p, const long long M) {
    vector<long long> f(M + 1);
    f[0] = 1;
    for (int i = 1; i <= M; i++) {
        if (i % p) {
            f[i] = (f[i - 1] * i) % M;
        } else {
            f[i] = f[i - 1];
        }
    }
    long long ans = 1;
    while (n > 1) {
        ans = ans * f[n % M] % M;
        ans = ans * modPow(f[M], n / M, M) % M;
        n /= p;
    }
    return ans;
}

long long legendre(long long n, long long p) {
    long long ans = 0;
    while (n > 0) {
        n /= p;
        ans += n;
    }
    return ans;
}

long long ncr(long long n, long long r, long long p, int k) {
    if (n < r || r < 0) {
        return 0;
    }
    long long M = 1;
    for (int i = 0; i < k; i++) {
        M *= p;
    }
    long long t = legendre(n, p) - legendre(r, p) - legendre(n - r, p);
    if (t >= k) {
        return 0;
    }
    long long ans = factMod(n, p, M) * modInverse(factMod(r, p, M), M) % M * modInverse(factMod(n - r, p, M), M) % M;
    ans = ans * modPow(p, t, M) % M;
    return ans;
}

pair<long long, long long> crt(long long a1, long long m1, long long a2, long long m2) {
    long long p, q;
    long long g = extendedEuclidean(m1, m2, p, q);
    if (a1 % g != a2 % g) {
        return make_pair(0, -1);
    }
    long long M = m1 / g * m2;
    p = (p % M + M) % M;
    q = (q % M + M) % M;
    return make_pair((p * a2 % M * (m1 / g) % M + q * a1 % M * (m2 / g) % M) % M, M);
}

long long ncr(long long n, long long r, long long M) {
    if (n < r || r < 0) {
        return 0;
    }
    pair<long long, long long> ans({0, 1});
    while (M > 1) {
        int p = spf[M], k = 0, cur = 1;
        while (M % p == 0) {
            M /= p; cur *= p;
            k++;
        }
        ans = crt(ans.first, ans.second, ncr(n, r, p, k), cur);
    }
    return ans.first;
}

int main() {
    IOS;
    sieve(N);
    int t;
    cin >> t;
    while (t--) {
        long long n, k, m;
        cin >> n >> k >> m;
        long long r = (n + k - 1) / k, x = (k - n % k) % k + r - 1, y = r - 1;
        long long ans = ncr(x, y, m);
        cout << r << " " << ans << endl;
    }
    return 0;
}
