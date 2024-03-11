//https://www.spoj.com/problems/RLTHREE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const int N = 2e5 + 5;

long long fact[N];

long long extendedEuclidean(long long a, long long b, long long *x, long long *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    ll x1, y1;
    ll gcd = extendedEuclidean(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

long long modInverse(long long b, long long m) {
    long long x, y;
    long long g = extendedEuclidean(b, m, &x, &y);
    if (g != 1) {
        return -1;
    }
    return (x % m + m) % m;
}

long long modDivide(long long a, long long b, long long m) {
    a = a % m;
    int inv = modInverse(b, m);
    return (inv * a) % m;
}

long long bin(long long n, long long k) {
    if (k < 0) {
        return 0;
    }
    if (k == 0) {
        return 1;
    }
    long long denom = fact[k] * fact[n - k];
    denom %= M;
    long long binomial = modDivide(fact[n], denom, M);
    return binomial;
}


int main() {
    IOS;
    string x, y, z;
    cin >> x >> y >> z;
    long long a = 0, b = 0, c = 0, ct = 0;
    for (int i = 0; i < x.size(); i++) {
        if (x[i] == '1' && y[i] == '0' && z[i] == '0') {
            a++;
        }
        if (x[i] == '0' && y[i] == '1' && z[i] == '0') {
            b++;
        }
        if (x[i] == '0' && y[i] == '0' && z[i] == '1') {
            c++;
        }
        if (x[i] == '1' && y[i] == '1' && z[i] == '0') {
            c++;
        }
        if (x[i] == '1' && y[i] == '0' && z[i] == '1') {
            b++;
        }
        if (x[i] == '0' && y[i] == '1' && z[i] == '1') {
            a++;
        }
        if (x[i] == '0' && y[i] == '0' && z[i] == '0') {
            ct++;
        }
        if (x[i] == '1' && y[i] == '1' && z[i] == '1') {
            ct++;
        }
    }
    if (a % 2 != b % 2 || a % 2 != c % 2) {
        cout << 0 << endl;
        return 0;
    }
    long long fc = 1;
    fact[0] = 1;
    for (long long i = 1; i < N; i++) {
        fc *= i;
        fc %= M;
        fact[i] = fc;
    }
    long long tot = 0;
    long long ans = 1;
    if (a > c)
        swap(a, c);
    if (a > b)
        swap(a, b);
    if (b > c)
        swap(b, c);

    for (int i = -a; i <= a; i += 2) {
        ans = 1;
        ans *= bin(a, (a + i) / 2);
        ans %= M;
        ans *= bin(b, (b + i) / 2);
        ans %= M;
        ans *= bin(c, (c + i) / 2);
        ans %= M;
        tot += ans;
    }
    for (int i = 0; i < ct; i++) {
        tot *= 2;
        tot %= M;
    }
    cout << tot << endl;

    return 0;
}
