//https://ocpc2026w.eolymp.space/en/compete/9umgdpquih09n7lf096jj2cqvk/problem/10
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 1e9 + 7;

ll modPow(ll a, ll y) {
    a %= M;
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

int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> a(n);
    vector<pair<int, int>> b;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    sort(a.begin(), a.end());
    for (int i = 0; i < n;) {
        int last = a[i], ct = 0;
        while (i < n && last == a[i]) {
            i++;
            ct++;
        }
        b.push_back({last, ct});
        for (auto [x, f] : b) {
            ll t = modPow(x + last, (M + 1) / 4);
            t = min(t, M - t);
            if (x != last) {
                t = t * 2 % M;
            }
            ans = (ans + t * f % M * ct % M) % M;
        }
    }
    cout << ans;
    return 0;
}
