//solution for https://cses.fi/problemset/task/1712/
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
        if (y & 1)
            res = (res * x) % m;
        y >>= 1;
        x = (x * x) % m;
    }
    return res;
}

int phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res -= res / i;
        }
    }
    if (n > 1) {
        res -= res / n;
    }
    return res;
}

int main() {
    IOS;
    int n;
    cin >> n;
    ll f = phi(M);
    for (int i = 0; i < n; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        ll pw = modPow(b, c, f);
        cout << modPow(a, pw, M) << endl;
    }
    return 0;
}
