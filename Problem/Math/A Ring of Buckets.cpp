//solution for https://dmoj.ca/problem/dmopc20c3p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 1e9 + 7;

ll modPow(ll x, ll y, ll m) {
    if (x == 0 && y == 0) {
        return 1;
    }
    ll res = 1;
    x = x % m;
    if (x == 0) {
        return 0;
    }
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % m;
        }
        y >>= 1;
        x = (x * x) % m;
    }
    return res;

}

ll modInverse(ll a, ll m) {
    ll res = 1;
    ll y = m - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}
ll modDivide(ll a, ll b, ll m) {
    a = a % m;
    ll inv = modInverse(b, m);
    return (inv * a) % m;
}

int main() {
    IOS;
    int q;
    cin >> q;
    while (q--) {
        ll n, m, k, b;
        cin >> n >> m >> k >> b;
        if (k == 1 && n % 3 == 0) {
            ll ct = n / 3;
            if (b == 1) {
                ll ans = (m * ct) % M;
                cout << ans << endl;
                continue;
            }
            ll bpw = (b * b) % M;
            ll pw = (((b * b) % M) * b) % M;
            ll frac = (m * ((bpw * ((modPow(pw, ct, M)) - 1)) % M)) % M;
            ll ans = modDivide(frac, pw - 1, M);
            cout << ans << endl;
            continue;
        }
        if (k == 2 && n % 2 == 0 && m % 2 == 0) {
            ll ct = n / 2;
            if (b == 1) {
                ll ans = (m * ct) % M;
                cout << ans << endl;
                continue;
            }
            ll mul = m / 2;
            ll pw = (b * b) % M;
            ll frac = (mul * ((b * ((modPow(pw, ct, M)) - 1)) % M)) % M;
            ll ans = modDivide(frac, pw - 1, M);
            cout << ans << endl;
            continue;
        }
        if (m < k + 2 || m % (k + 2) != 0) {
            cout << -1 << endl;
            continue;
        }
        ll p = m / (k + 2);
        if (b == 1) {
            ll ans = (n * p) % M;
            cout << ans << endl;
            continue;
        }
        ll ans = modDivide((p * (modPow(b, n, M) - 1)) % M, b - 1, M);
        cout << ans << endl;


    }
    return 0;
}
