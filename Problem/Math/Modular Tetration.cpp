//https://judge.yosupo.jp/problem/tetration_mod
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

map<int, int> mp;

long long mod(long long x, long long m) {
    if (x < m) {
        return x;
    }
    return x % m + m;
}

long long modPow(long long a, long long y, long long m) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = mod(res * a, m);
        }
        y /= 2;
        a = mod(a * a, m);
    }
    return res;
}

int phi(int n) {
    auto it = mp.find(n);
    if (it != mp.end()) {
        return it->second;
    }
    int res = n, t = n;
    for (int i = 2; i <= sqrt(t); i++) {
        if (t % i == 0) {
            while (t % i == 0) {
                t /= i;
            }
            res -= res / i;
        }
    }
    if (t > 1) {
        res -= res / t;
    }
    return mp[n] = res;
}

long long calc(int l, int r, long long m, long long a) {

    if (l == r) {
        return mod(a, m);
    }
    if (m == 1) {
        return 1;
    }
    return modPow(a, calc(l + 1, r, phi(m), a), m);
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b, m;
        cin >> a >> b >> m;
        if (a == 0) {
            cout << (b % 2 == 0) % m << endl;
        } else if (b == 0) {
            cout << 1 % m << endl;
        } else {
            cout << calc(1, b, m, a) % m << endl;
        }
    }

    return 0;
}
