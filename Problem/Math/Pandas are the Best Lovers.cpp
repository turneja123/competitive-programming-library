//https://www.spoj.com/problems/PALOVE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

bool b[N];

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
	int p; cin >> p;
	for (int i = 1; i < p; i++) {
        if (tonelli_shanks(i, p) != -1) {
            b[i] = true;
        }
	}
	if (p < 200) {
        for (int x1 = 1; x1 < p; x1++) {
            if (!b[x1]) {
                continue;
            }
            for (int y1 = 1; y1 < p; y1++) {
                if (b[y1]) {
                    int x2 = x1 + y1, y2 = p + x1 - x2;
                    if (b[y2] && b[x2]) {
                        cout << 2 << endl;
                        cout << tonelli_shanks(x1, p) << " " << tonelli_shanks(x2, p) << endl;
                        cout << tonelli_shanks(y1, p) << " " << tonelli_shanks(y2, p) << endl;
                        return 0;
                    }
                }
            }
        }
	}
	for (int x1 = 1; x1 < p; x1++) {
        if (!b[x1]) {
            continue;
        }
        for (int y1 = 1; y1 < p; y1++) {
            if (b[y1]) {
                int x2 = x1 + y1;
                if (b[x2]) {
                    for (int y2 = 1; y2 < p; y2++) {
                        int x3 = x2 + y2, y3 = p + x1 - x3;
                        if (b[y2] && b[x3] && b[y3]) {
                            cout << 3 << endl;
                            cout << tonelli_shanks(x1, p) << " " << tonelli_shanks(x2, p) << " " << tonelli_shanks(x3, p) << endl;
                            cout << tonelli_shanks(y1, p) << " " << tonelli_shanks(y2, p) << " " << tonelli_shanks(y3, p) << endl;
                            return 0;
                        }
                    }
                }
            }
        }
	}
	return 0;
}
