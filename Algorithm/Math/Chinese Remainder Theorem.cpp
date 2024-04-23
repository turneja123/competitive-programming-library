//https://open.kattis.com/problems/chineseremainder
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long extendedEuclidean(long long a, long long b, long long *x, long long *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    long long x1, y1;
    long long gcd = extendedEuclidean(b % a, a, &x1, &y1);
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

long long crt(vector<pair<long long, long long>> &v) {
    long long M = 1;
    for (int i = 0; i < v.size(); i++) {
        M *= v[i].second;
    }
    __int128 ans = 0;
    for (int i = 0; i < v.size(); i++) {
        long long m = M / v[i].second;
        long long n = modInverse(m, v[i].second);
        ans = (ans + (__int128)v[i].first * m % M * n) % M;
    }
    return (long long)ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long a, n, b, m;
        cin >> a >> n >> b >> m;
        vector<pair<long long, long long>> v{{a, n}, {b, m}};
        cout << crt(v) << " " << n * m << endl;
    }

    return 0;
}
