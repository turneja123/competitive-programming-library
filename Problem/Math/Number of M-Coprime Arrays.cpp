//https://www.hackerrank.com/contests/infinitum17/challenges/number-of-m-coprime-arrays/problem
#pragma GCC optimize("Ofast,fast-math")
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
const unsigned long long M = 1e9 + 7;
int L = 300;


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

long long rho(long long n) {
    long long c = rand() % (n + 1);
    long long x = rand() % (n + 1);
    long long xx = x;
    long long g = 1;
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

vector<long long> mul(int n, vector<long long> &a, vector<long long> &b, vector<long long> &tr) {
    vector<long long> res(n * 2 + 1, 0);
    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            res[i + j] = (res[i + j] + a[i] * b[j]) % M;
        }
    }
    for (int i = 2 * n; i > n; --i) {
        for (int j = 0; j < n; j++) {
            res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % M;
        }
    }
    res.resize(n + 1);
    return res;
}

long long solve(vector<long long> &c, vector<long long> &s, long long k) {
    int n = c.size();
    if (n == 0) {
        return 0;
    }
    if (k < 0) {
        return 0;
    }
    if (k < n) {
        return s[k];
    }
    vector<long long> x(n + 1), a(x);
    x[0] = 1, a[1] = 1;
    for (++k; k; k /= 2) {
        if (k % 2) {
            x = mul(n, x, a, c);
        }
        a = mul(n, a, a, c);
    }
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res = (res + x[i + 1] * s[i]) % M;
    }
    return res;
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
    int t;
    cin >> t;
    while (t--) {
        factors.clear();
        ans.clear();
        a.clear();
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
        ans.resize(min((long long)L, (long long)n));
        int bits = 1 << (a.size());
        vector<long long> c;
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
        for (int i = 1; i < min((long long)L, (long long)n); i++) {
            for (int j = 0; j < bits; j++) {
                dp[i][j] = dp[i - 1][j];
            }
            for (int k = 0; k < a.size(); k++) {
                for (int j = 0; j < bits; j++) {
                    if (j & (1 << k)) {
                        dp[i][j] += dp[i][j ^ (1 << k)];
                    }
                }
            }
            vector<long long> temp(bits, 0);
            for (int j = 0; j < bits; j++) {
                temp[j] = dp[i][j] % M;
            }
            for (int j = 0; j < bits; j++) {
                int complement = (bits - 1) ^ j;
                dp[i][j] = (temp[complement] * aux[j]) % M;
                ans[i] += dp[i][j];
            }
            ans[i] %= M;
            if (i % 33 == 0) {
                vector<long long> s(ans.begin(), ans.begin() + i + 1);
                c = berlekamp_massey(s);
                if (2 * c.size() < i) {
                    break;
                }
            }
        }
        if (n <= L) {
            cout << ans[n - 1] << endl;
            continue;
        }
        if (c.size() == 0) {
            c = berlekamp_massey(ans);
        }
        ans.resize(c.size());
        cout << solve(c, ans, n - 1) << endl;
    }
    return 0;
}
