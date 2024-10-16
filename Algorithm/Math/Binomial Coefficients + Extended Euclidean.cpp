//solution for https://cses.fi/problemset/task/1079/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 1e9 + 7;
const int N = 1e6 + 5;

ll fact[N];

ll extendedEuclidean(ll a, ll b, ll *x, ll *y) {
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

ll modInverse(ll b, ll m) {
    ll x, y;
    ll g = extendedEuclidean(b, m, &x, &y);
    if (g != 1) {
        return -1;
    }
    return (x % m + m) % m;
}

ll modDivide(ll a, ll b, ll m) {
    a = a % m;
    int inv = modInverse(b, m);
    return (inv * a) % m;
}

int main() {
    IOS;
    ll f = 1;
    fact[0] = 1;
    for (ll i = 1; i < N; i++) {
        f *= i;
        f %= M;
        fact[i] = f;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        ll n, k;
        cin >> n >> k;
        ll denom = fact[k] * fact[n - k];
        denom %= M;
        ll binomial = modDivide(fact[n], denom, M);
        cout << binomial << endl;
    }
    return 0;
}
