//https://www.spoj.com/problems/ADADIGIT/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<int> primes = {2, 7, 61};
vector<long long> factors;

int d[10];

long long mult(long long x, long long y, long long m){
    long long k = (x * (double)y / m) + 0.5, r = x * y - k * m;
    return r < 0 ? r + m : r;
}

long long f(long long x, long long c, long long mod) {
    return mult(x, x, mod) + c;
}

long long binpower(long long base, long long e, long long mod) {
    long long result = 1;
    base %= mod;
    while (e) {
        if (e & 1) {
            result = mult(result, base, mod);
        }
        base = mult(base, base, mod);
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

bool check_composite(long long n, long long a, long long d, int s) {
    long long x = binpower(a, d, n);
    if (x == 1 || x == n - 1) {
        return false;
    }
    for (int r = 1; r < s; r++) {
        x = mult(x, x, n);
        if (x == n - 1) {
            return false;
        }
    }
    return true;
};


bool is_prime(long long n) {
    if (n < 2) {
        return false;
    }
    int r = 0;
    long long d = n - 1;
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

void factor(long long n) {
    if (n == 1) {
        return;
    }
    if (is_prime(n)) {
        factors.push_back(n);
        return;
    }

    long long divisor = rho(n);
    factor(divisor);
    factor(n / divisor);
    return;
}

pair<long long, long long> solve(long long n) {
    factor(n);
    sort(factors.begin(), factors.end());
    int i = 0, j = 0, m = factors.size();
    long long a = 1, b = 1;
    while (i < m) {
        long long cur = factors[i], pw = cur;
        while (i < m && factors[i] == cur) {
            i++;
            pw *= cur;
        }
        a *= (i - j + 1);
        b *= (pw - 1) / (cur - 1);
        j = i;
    }
    factors.clear();
    return make_pair(a, b);
}

int main() {
    IOS;
    srand(time(NULL));
    long long n, mxa = 0, mxb = 0, ansa = -1, ansb = -1;
    cin >> n;
    vector<int> pos;
    for (int i = 0; i < n; i++) {
        cin >> d[i];
        pos.push_back(i + 1);
    }
    do {
        int m = 0, pw = 1;
        for (int i = 0; i < n; i++) {
            m += d[pos[i] - 1] * pw;
            pw *= 10;
        }
        pair<long long, long long> ans = solve(m);
        long long a = ans.first, b = ans.second;
        if (a > mxa) {
            mxa = a;
            ansa = m;
        } else if (a == mxa && m < ansa) {
            ansa = m;
        }
        if (b > mxb) {
            mxb = b;
            ansb = m;
        } else if (b == mxb && m < ansb) {
            ansb = m;
        }

    } while (next_permutation(pos.begin(), pos.end()));
    cout << ansa << " " << ansb;


    return 0;
}
