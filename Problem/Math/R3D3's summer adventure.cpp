//https://dmoj.ca/problem/bbc09i
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e18;

ll binomial(ll n, ll k) {
    if (k > n) {
        return 0;
    }
    ll ans = 1;
    for (int i = 1; i <= k; i++) {
        __int128 tmp = (__int128)ans * (n - k + i) / i;
        if (tmp >= INF) {
            return INF;
        }
        ans = tmp;
    }
    return ans;
}

ll calc(ll x, ll k, ll c0, ll c1) {
    ll ct = 0;
    for (int j = 0; j * c1 <= x; j++) {
        ct += binomial((x - j * c1) / c0 + j + 1, j + 1);
        if (ct >= k) {
            return k;
        }
    }
    return ct;
}

int main() {
    IOS;
    ll n, c0, c1;
    cin >> n >> c0 >> c1;
    if (c0 > c1) {
        swap(c0, c1);
    }
    ll k = n - 1;
    if (c0 == 0) {
        cout << k * c1;
        return 0;
    }
    ll l = 0, r = k * c0, spl = 0;
    while (l <= r) {
        ll mid = (l + r) / 2;
        if (calc(mid, k, c0, c1) >= k) {
            spl = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    ll ct = 0, ans = k * (c0 + c1);
    for (int j = 0; j * c1 < spl; j++) {
        ll m = (spl - 1 - j * c1) / c0;
        ll ways = binomial(m + j + 1, j + 1);
        ct += ways;
        ans += ways * j * c1 + binomial(m + j + 1, j + 2) * (j + 1) * c0;
    }
    ans += (k - ct) * spl;
    cout << ans;

    return 0;
}
