//https://ocpc2026w.eolymp.space/en/compete/rofq4l68mt2dp1esn9ncjjllcg/problem/12
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
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

ll s(int l, int r, vector<ll> &p) {
    return (p[r] - (l == 0 ? 0 : p[l - 1]) + M) % M;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    ll ans = (1 + m + (ll)m * (m - 1) % M * modPow(2, M - 2) % M * modPow(2, M - 2) % M) % M;

    int i = 0;
    while (i < m) {
        int last = a[i], st = i;
        while (i < m && last == a[i]) {
            i++;
        }
        int n = i - st;
        ans = (ans - (ll)n * (n - 1) % M * modPow(2, M - 2) % M * modPow(2, M - 2) % M + M) % M;
    }
    vector<ll> pref(m), prefs(m);
    for (int i = 0; i < m; i++) {
        ll c = a[i] * modPow(n, M - 2) % M;
        ll cs = c * c % M;

        pref[i] = ((i == 0 ? 0 : pref[i - 1]) + c) % M;
        prefs[i] = ((i == 0 ? 0 : prefs[i - 1]) + cs) % M;
        if (i == 0) {
            continue;
        }

        int l = 0, r = i - 1, spl = i;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (a[i] - a[mid] <= n - a[i] + a[mid]) {
                spl = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        if (spl < i) {
            ans = (ans - (ll)(i - spl) * c % M + s(spl, i - 1, pref) + M) % M;
            ans = (ans + (ll)(i - spl) * cs + s(spl, i - 1, prefs) - (ll)2 * s(spl, i - 1, pref) % M * c % M + M) % M;
        }
        spl--;
        if (spl >= 0) {
            ans = (ans + (ll)(spl + 1) * c % M - (ll)(spl + 1) + M - s(0, spl, pref) + M) % M;
            ans = (ans + (ll)(spl + 1) + (ll)(spl + 1) * cs % M + s(0, spl, prefs)
                     + (ll)2 * s(0, spl, pref) % M - (ll)(spl + 1) * 2 % M * c % M + M - (ll)2 * c * s(0, spl, pref) % M + M) % M;
        }
        /*for (int j = i - 1; j >= 0; j--) {
            if (a[i] == a[j]) {
                continue;
            }
            int d = min(a[i] - a[j], n - a[i] + a[j]);
            ll p = d * modPow(n, M - 2)  % M;
            ans = (ans + modPow(2, M - 2) + p * p % M - p + M) % M;
        }*/
    }
    cout << ans << endl;
    return 0;
}
