//https://www.spoj.com/problems/COPSEQH/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
vector<long long> factors;
vector<long long> a;

const int N = 1e5 + 5;
const int K = 1 << 15;
const long long M = 1e9 + 7;
int L = 40;


long long dp[405][K];
vector<long long> ans;
long long aux[K];

__int128 mult(__int128 a, __int128 b, __int128 mod) {
    return (__int128)a * b % mod;
}

__int128 f(__int128 x, __int128 c, __int128 mod) {
    return (mult(x, x, mod) + c) % mod;
}

__int128 binpower(__int128 base, __int128 e, __int128 mod) {
    __int128 result = 1;
    base %= mod;
    while (e) {
        if (e & 1) {
            result = (__int128)result * base % mod;
        }
        base = (__int128)base * base % mod;
        e >>= 1;
    }
    return result;
}

__int128 rho(__int128 n) {
    __int128 c = rand() % (n + 1);
    __int128 x = rand() % (n + 1);
    __int128 xx = x;
    __int128 g = 1;
    if (n % 2 == 0) {
        return 2;
    }

    while (g == 1) {
        x = f(x, c, n);
        xx = f(xx, c, n);
        xx = f(xx, c, n);
        g = __gcd(abs(x - xx), n);
    }
    return g;
}

bool check_composite(__int128 n, __int128 a, __int128 d, int s) {
    __int128 x = binpower(a, d, n);
    if (x == 1 || x == n - 1) {
        return false;
    }
    for (int r = 1; r < s; r++) {
        x = (__int128)x * x % n;
        if (x == n - 1) {
            return false;
        }
    }
    return true;
};


bool is_prime(__int128 n) {
    if (n < 2) {
        return false;
    }
    int r = 0;
    __int128 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for (int a : primes) {
        if (n == a) {
            return true;
        }
        if (check_composite(n, a, d, r)) {
            return false;
        }
    }
    return true;
}

void factor(__int128 n) {
    if (n == 1) {
        return;
    }
    if (is_prime(n)) {
        factors.push_back(n);
        return;
    }

    __int128 divisor = rho(n);
    factor(divisor);
    factor(n / divisor);
    return;
}

long long modInverse(long long a, long long m) {
    long long res = 1;
    long long y = m - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}

vector<long long> berlekamp_massey(vector<long long> s) {
    int n = s.size(), l = 0, m = 0;
    vector<long long> c(n), b(n), t(n);
    c[0] = 1, b[0] = 1;
    long long d = 1;
    for (int i = 0; i < n; i++) {
        m++;
        long long d_next = s[i];
        for (int j = 1; j <= l; j++) {
            d_next = (d_next + (c[j] * s[i - j]) % M) % M;
        }
        if (d_next == 0) {
            continue;
        }
        t = c;
        long long coef = (d_next * modInverse(d, M)) % M;
        for (int j = m; j < n; j++) {
            c[j] = (c[j] - (coef * b[j - m]) % M + M) % M;
        }
        if (2 * l > i) {
            continue;
        }
        l = i + 1 - l, b = t, d = d_next, m = 0;
    }
    c.resize(l + 1);
    c.erase(c.begin());
    for (int i = 0; i < l; i++) {
        c[i] *= -1;
        c[i] = (c[i] + M) % M;
    }
    return c;
}

int main() {
    IOS;
    srand(time(NULL));
    long long n, m;
    cin >> n >> m;
    factor(m);
    sort(factors.begin(), factors.end());
    int i = 0, j = 0, k = factors.size();
    while (i < k) {
        long long cur = factors[i];
        while (i < k && factors[i] == cur) {
            i++;
        }
        a.push_back(i - j);
        j = i;
    }
    if (a.size() < 14) {
        L = 200;
        if (a.size() < 13) {
            L = 400;
        }
    }
    ans.resize(min(L, (int)n));
    int bits = 1 << (a.size());
    for (int j = 0; j < bits; j++) {
        long long ways = 1;
        for (int k = 0; k < a.size(); k++) {
            int c = j & (1 << k);
            if (c > 0) {
                ways = (ways * a[k]) % M;
            }
        }
        aux[j] = ways;
        dp[0][j] = aux[j];
        ans[0] = (ans[0] + (long long)dp[0][j]) % M;
    }
    for (int i = 1; i < min(L, (int)n); i++) {
        for (int j = 1; j < bits; j++) {
            int complement = (bits - 1) ^ j;
            long long sum = 0;
            for (int s = complement; s; s = (s - 1) & complement) {
                sum = (sum + dp[i - 1][s] * aux[j]) % M;
            }
            dp[i][j] = (((ans[i - 1] - (i == 1)) * aux[j]) % M - sum + M) % M;
            ans[i] = (ans[i] + (long long)dp[i][j]) % M;
        }
    }
    if (n <= L) {
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        return 0;
    }
    vector<long long> c = berlekamp_massey(ans);
    ans.resize(n);
    for (int i = 0; i < c.size(); i++) {
        cout << ans[i] << " ";
    }
    for (int i = c.size(); i < n; i++) {
        ans[i] = 0;
        for (int j = 0; j < c.size(); j++) {
            ans[i] = (ans[i] + ans[i - j - 1] * c[j]) % M;
        }
        cout << ans[i] << " ";
    }

    return 0;
}
