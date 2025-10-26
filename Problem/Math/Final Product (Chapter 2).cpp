//https://www.facebook.com/codingcompetitions/hacker-cup/2025/round-1/problems/B2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const int N = 1e5 + 5;

long long inv[N];
long long fact[N];
long long factinv[N];

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
vector<long long> factors;

ll m, x, n;

ll ans = 0;

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

ll binomial(ll n, ll k) {
    ll prod = 1;
    for (ll i = k + 1; i <= n; i++) {
        prod = prod * (i % M) % M;
    }
    prod = prod * factinv[n - k] % M;
    return prod;
}
void get_divs(int i, long long cur, vector<pair<long long, int>> &f, vector<pair<long long, int>> &v) {
    if (i == f.size()) {

        if (cur <= x) {
            ll A = 1;
            ll B = 1;
            for (int j = 0; j < f.size(); j++) {
                int ea = v[j].second;
                int eb = f[j].second - v[j].second;
                if (ea > 0) {
                    A = A * binomial(ea + m - 1, m - 1) % M;
                }
                if (eb > 0) {
                    B = B * binomial(eb + m - 1, m - 1) % M;
                }
            }
            ans = (ans + A * B) % M;
        }
        return;
    }
    for (int j = 0; j <= f[i].second; j++) {
        v[i].first = f[i].first, v[i].second = j;
        get_divs(i + 1, cur, f, v);
        cur *= f[i].first;

    }
    return;
}


int main() {
    IOS;
    freopen("1.txt", "r", stdin);
    freopen("2.txt", "w", stdout);
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    srand(time(NULL));
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        cin >> m >> x >> n;
        factor(n);
        sort(factors.begin(), factors.end());
        vector<pair<long long, int>> f;
        int i = 0, j = 0, z = factors.size();
        while (i < z) {
            long long cur = factors[i];
            while (i < z && factors[i] == cur) {
                i++;
            }
            f.push_back(make_pair(factors[j], i - j));
            j = i;
        }
        vector<pair<ll, int>> v(f.size());
        ans = 0;
        get_divs(0, 1, f, v);
        factors.clear();
        cout << "Case #" << tt << ": " << ans << endl;
    }

    return 0;
}
