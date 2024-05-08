//https://projecteuler.net/problem=885
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

long long M = 1123455689;

long long f[20];

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

long long ans = 0;

void calc(int i, int ct, int n, vector<int> &v) {
    if (ct > n) {
        return;
    }
    if (v[0] == n) {
        return;
    }
    if (i == 10 && ct != n) {
        return;
    }
    if (i == 10 && ct == n) {
        long long a = 0, denom = 1; vector<int> d;
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < v[j]; k++) {
                d.push_back(j);
            }
            denom = (denom * f[v[j]]) % M;
        }
        for (int j = 0; j < d.size(); j++) {
            a += d[j];
            if (j != d.size() - 1) {
                a *= (long long)10;
            }
        }
        a %= M;
        long long ways = f[n] * modPow(denom, M - 2) % M;
        if (v[0] > 0) {
            denom = denom * modPow(f[v[0]], M - 2) % M;
            denom = denom * f[v[0] - 1] % M;
            ways = (ways - f[n - 1] * modPow(denom, M - 2) % M + M) % M;
        }
        ans = (ans + a * ways % M) % M;
        return;
    }
    for (int j = 0; j <= n; j++) {
        v[i] = j;
        calc(i + 1, ct + j, n, v);
        v[i] = 0;
    }
}

int main() {
   // IOS;
    f[0] = 1;
    for (int i = 1; i < 20; i++) {
        f[i] = (f[i - 1] * i) % M;
    }
    for (int n = 1; n <= 18; n++) {
        vector<int> v(10, 0);
        calc(0, 0, n, v);
        cout << n << " " << ans << endl;
    }
    return 0;
}
