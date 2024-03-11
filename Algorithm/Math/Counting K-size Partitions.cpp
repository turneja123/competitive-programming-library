#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 1e9 + 7;
const int N = 2e6 + 5;

ll f[N];

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
    int n, k;
    cin >> k >> n;
    f[0] = 1;
    for (int i = 1; i < N; i++) {
        f[i] = f[i - 1] * i;
        f[i] %= M;
    }
    ll denom = f[n] * f[k - 1];
    denom %= M;
    ll sol = modDivide(f[n + k - 1], denom, M);
    cout << sol;
    return 0;
}
