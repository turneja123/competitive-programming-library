//https://codeforces.com/contest/622/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 1e6 + 5;
const long long M = 1e9 + 7;

long long y[K];
long long pref[K];
long long suf[K];
long long inv[K];

long long modPow(long long a, long long y, long long m) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}

long long lagrange(long long n, int k) {
    int deg = k + 1;
    y[0] = 0;
    for (int i = 1; i <= deg; i++) {
        y[i] = (y[i - 1] + modPow(i, k, M)) % M;
    }
    if (n <= deg) {
        return y[n];
    }
    inv[0] = 1;
    pref[0] = n, suf[deg] = n - deg;
    for (int i = 1; i < deg; i++) {
        pref[i] = (pref[i - 1] * (n - i)) % M;
    }
    for (int i = deg - 1; i >= 0; i--) {
        suf[i] = (suf[i + 1] * (n - i)) % M;
    }
    for (int i = 1; i <= deg; i++) {
        inv[i] = (inv[i - 1] * modPow(i, M - 2, M)) % M;
    }
    long long ans = 0;
    for (int i = 0; i <= deg; i++) {
        long long num, denom;
        if (i == 0) {
            num = suf[1];
        } else if (i == deg) {
            num = pref[deg - 1];
        } else {
            num = pref[i - 1] * suf[i + 1] % M;
        }
        denom = inv[i] * inv[deg - i] % M;
        if ((deg - i) % 2 == 0) {
            ans = (ans + ((y[i] * num % M) * denom) % M) % M;
        } else {
            ans = (ans - ((y[i] * num % M) * denom) % M + M) % M;
        }
    }
    return ans;
}

int main() {
    IOS;
    long long n, k;
    cin >> n >> k;
    cout << lagrange(n, k);

    return 0;
}
