//bbc15
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 998244353;

ll modPow(ll a, ll y) {
    ll res = 1;
    while (y > 0) {
        if (y % 2 != 0) {
            res = res * a % M;
        }
        y /= 2;
        a = a * a % M;
    }
    return res;
}

ll pref(ll n) {
    return modPow(2, n + 1) - 1;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        if (n % 2 == 0) {
            ll ans = (pref(n - 1) - pref(n / 2 - 1) + M - modPow(2, n / 2 - 1) * (n / 2% M) % M + M) % M;
            ans = ans * modPow(modPow(2, n), M - 2) % M;
            cout << ans << endl;
        } else {
            ll ans = modPow(2, n - 1);
            if (n != 1) {
                ans += (pref(n - 2) - pref(n / 2) + M - modPow(2, n / 2) * (n / 2 % M - 1 + M) % M + M) % M;
                ans %= M;
            }
            ans = ans * modPow(modPow(2, n), M - 2) % M;
            cout << ans << endl;
        }
    }
    return 0;
}
