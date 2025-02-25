//https://www.spoj.com/problems/SPY2/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define MOD (I==0?A:I==1?B:I==2?C:D)
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

const unsigned int A=9,B=5,C=19,D=1169593;

using ll = long long;
ll fact[N];
ll finv[N];
ll legendre[N];
int I;
int mp;

ll mpow(ll a, ll y) {
    ll res = 1;
    while (y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % MOD;
        }
        y /= 2;
        a = (a * a) % MOD;
    }
    return res;
}

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll x1, y1;
    ll d = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

ll minv(ll a, ll M) {
    ll x, y;
    ll g = exgcd(a, M, x, y);
    if (g != 1) {
        assert(0);
        return -1;
    }
    return (x % M + M) % M;
}

bool flag = false;

ll binom(int n, int k, ll p) {
    if (legendre[n - 1] - legendre[n - k] - legendre[k] < 0) {
        flag = true;
    }
    return fact[n - 1] * finv[n - k] % MOD * finv[k] % MOD * mpow(p, max(0ll, legendre[n - 1] - legendre[n - k] - legendre[k])) % MOD;
}

ll crt(vector<pair<ll, ll>> &v) {
    ll M = 1;
    for (int i = 0; i < v.size(); i++) {
        M *= v[i].second;
    }
    ll ans = 0;
    for (int i = 0; i < v.size(); i++) {
        ll m = M / v[i].second;
        ll n = minv(m, v[i].second);
        ans = (ans + v[i].first * m % M * n) % M;
    }
    return ans;
}

ll calc(int n, int l, ll p) {
    fact[0] = 1;
    for (int i = 1; i <= n + 1; i++) {
        int j = i;
        legendre[i] = legendre[i - 1];
        while (j % p == 0) {
            j /= p;
            legendre[i]++;
        }
        fact[i] = fact[i - 1] * j % MOD;
    }
    finv[n + 1] = minv(fact[n + 1], MOD);
    for (int i = n; i > 0; i--) {
        int j = i + 1;
        while (j % p == 0) {
            j /= p;
        }
        finv[i] = finv[i + 1] * j % MOD;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        flag = false;
        long long add = (i % 2 ? 1 : (MOD - 1)) * binom(n + 1, i, p) % MOD;
        if (!flag) {
            add *= mpow(n + 1 - i, l) % MOD;
        } else {
            add *= mpow(n + 1 - i, l - 1) % MOD * ((n + 1 - i) / p) % MOD;
        }
        ans = (ans + add) % MOD;
    }

    return ans;
}

int main() {
    //IOS;
    int n, l;
    while (cin>>n>>l) {
        map<int, int> factors;
        factors[3] = 2;
        factors[5] = 1;
        factors[1169593] = 1;
        factors[19] = 1;

        vector<pair<ll, ll>> v;
        int j =0;
        for (auto [p, e] : factors) {
            ll pe = 1;
            for (int j = 0; j < e; j++) {
                pe *= p;
            }
            I = j;
            mp = j++;
            v.push_back(make_pair(calc(n, l, p), pe));
        }
        ll ans = crt(v);
        long long lans = ans;
        cout << lans << endl;
    }
    return 0;
}
