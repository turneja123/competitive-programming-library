//https://atcoder.jp/contests/abc397/tasks/abc397_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
vector<long long> factors;
vector<long long> expo;

long long n;

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

void get_divs(int i, long long cur, vector<pair<long long, int>> &f, vector<long long> &divs) {
    if (i == f.size()) {
        divs.push_back(cur);

        return;
    }
    for (int j = 0; j <= f[i].second; j++) {
        get_divs(i + 1, cur, f, divs);
        cur *= f[i].first;
    }
    return;
}


int main() {
    IOS;
    srand(time(NULL));
    cin >> n;
    factor(n);
    sort(factors.begin(), factors.end());
    expo.resize(factors.size());
    vector<pair<long long, int>> f;
    int i = 0, j = 0, m = factors.size(), d = 1;
    while (i < m) {
        long long cur = factors[i];
        while (i < m && factors[i] == cur) {
            expo[i] = d;
            i++;
        }
        f.push_back(make_pair(factors[j], i - j));
        d *= i - j + 1;
        j = i;
    }

    vector<long long> divs;
    get_divs(0, 1, f, divs);
    for (long long z : divs) {
        long long p = n / z;
        __int128 D = ((__int128)p * 4 - (__int128)z * z) * (__int128)3;
        if (D < 0) {
            continue;
        }
        long long l = 0, r = 1e15, sq = 0;
        while (l <= r) {
            long long mid = (l + r) / 2;
            __int128 prod = (__int128)mid * mid;
            if (prod <= D) {
                sq = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (sq * sq != D) {
            continue;
        }
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0) {
                continue;
            }
            long long x = z * 3 + sq * dx;
            if (x % 6 != 0) {
                continue;
            }
            x /= 6;
            long long y = x - z;
            if (x <= 0 || y <= 0) {
                continue;
            }
            cout << x << " " << y;
            return 0;
        }
    }
    cout << -1;

    return 0;
}
