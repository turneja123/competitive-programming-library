//https://www.spoj.com/problems/NUMTRY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int D = 2e5 + 5;
const long long M = 1e9 + 7;

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
vector<long long> factors;
vector<long long> expo;

long long n;
int idx = 0;

pair<pair<long long, long long>, long long> masks[D];

long long a[D];

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

void get_divs(int i, long long cur, long long mask, long long h, int bit, vector<pair<long long, int>> &f, vector<pair<long long, int>> &v) {
    if (i == f.size()) {
        long long m = n / cur;
        masks[idx++] = make_pair(make_pair(mask, h), cur);
        a[h] = m;

        return;
    }
    for (int j = 0; j <= f[i].second; j++) {
        v[i].first = f[i].first, v[i].second = j;
        get_divs(i + 1, cur, mask, h, bit + f[i].second, f, v);
        cur *= f[i].first;
        mask += 1ll << (bit + j), h += expo[bit + j];
    }
    v[i] = make_pair(0, 0);
    return;
}

bool valid(int h, int i, long long mask) {
    if (i != factors.size() - 1) {
        long long c = mask & (1ll << (i + 1));
        if (expo[i] == expo[i + 1] && c) {
            return false;
        }
    }
    return true;
}

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

int main() {
    IOS;
    srand(time(NULL));
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        long long sq = sqrt(n);
        if (sq * sq == n && is_prime(sq)) {
            factors.push_back(sq);
            factors.push_back(sq);
        } else {
            factor(n);
        }
        sort(factors.begin(), factors.end());
        expo.resize(factors.size());
        vector<pair<long long, int>> f;
        int i = 0, j = 0, m = factors.size(), d = 1;
        long long fn = 1;
        while (i < m) {
            long long cur = factors[i];
            while (i < m && factors[i] == cur) {
                expo[i] = d;
                i++;
            }
            f.push_back(make_pair(factors[j], i - j));

            fn = (fn * (modPow(cur % M, 2 * (i - j) + 1) + 1)) % M;
            d *= i - j + 1;
            j = i;
        }

        vector<pair<long long, int>> v(f.size());
        get_divs(0, 1, 0, 0, 0, f, v);

        for (int i = 0; i < factors.size(); i++) {
            for (int k = 0; k < d; k++) {
                long long j = masks[k].first.first, h = masks[k].first.second, c = j & (1ll << i);
                if (c) {
                    long long sub = h - expo[i];
                    if (valid(sub, i, j)) {
                        a[sub] -= a[h];
                    }
                }
            }
        }
        long long gn = 0;
        for (int k = 0; k < d; k++) {
            long long b = masks[k].second, h = masks[k].first.second;
            a[h] %= M;
            __int128 add = (__int128)n * a[h] / b;
            gn += add % M;
        }
        cout << fn * modPow(gn % M, M - 2) % M << endl;
        factors.clear();
        expo.clear();
        idx = 0;
    }

    return 0;
}
