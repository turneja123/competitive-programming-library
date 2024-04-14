//https://judge.yosupo.jp/problem/sqrt_mod
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long modPow(long long x, long long y, long long M) {
    if (x == 0 && y == 0) {
        return 1;
    }
    long long res = 1;
    x = x % M;
    if (x == 0) {
        return 0;
    }
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % M;
        }
        y >>= 1;
        x = (x * x) % M;
    }
    return res;
}

long long tonelli_shanks(long long a, long long p) {
    if (a == 0) {
        return 0;
    }
    if (modPow(a, (p - 1) / 2, p) != 1) {
        return -1;
    }
    if (p % 4 == 3) {
        return modPow(a, (p + 1) / 4, p);
    }
    long long s = p - 1, n = 2, r = 0;
    while (s % 2 == 0) {
        r++;
        s /= 2;
    }
    while (modPow(n, (p - 1) / 2, p) != p - 1) {
        n++;
    }
    long long x = modPow(a, (s + 1) / 2, p), b = modPow(a, s, p), g = modPow(n, s, p), m = 1;
    while (m) {
        long long t = b;
        m = 0;
        for (; m < r && t != 1; m++) {
            t = (t * t) % p;
        }
        if (m == 0) {
            return x;
        }
        long long gs = modPow(g, 1 << (r - m - 1), p);
        g = (gs * gs) % p;
        x = (x * gs) % p;
        b = (b * g) % p;
        r = m;
    }
    return 0;
}


int main() {
	IOS;
	int t;
	cin >> t;
	while (t--) {
        int y, p;
        cin >> y >> p;
        cout << tonelli_shanks(y, p) << endl;
	}

	return 0;
}
