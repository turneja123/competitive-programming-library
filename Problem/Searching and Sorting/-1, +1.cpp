//https://atcoder.jp/contests/abc459/tasks/abc459_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e12;

ll s(ll n) {
    return n * (n + 1) / 2;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n + 1);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        a.back() = INF;
        ll last = a.back();
        multiset<pair<int, ll>> gaps;
        ll ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] < last) {
                if (last - a[i] > 1) {
                    gaps.insert({i, last - a[i] - 1});
                }
                last = a[i];
                continue;
            }
            while (a[i] >= last) {
                auto [j, ct] = *gaps.begin();
                ll m = j - i;
                ll x = a[i] - ct * m, y = last + ct;
                if (x >= y) {
                    ans += s(m) * ct;
                    a[i] = x;
                    last = y;
                    gaps.erase(gaps.begin());
                    continue;
                }

                ll l = 1, r = ct * m, spl = -1;
                while (l <= r) {
                    ll mid = (l + r) / 2;

                    ll x = a[i] - mid;
                    ll y = last + mid / m;
                    if (x < y) {
                        spl = mid;
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                    }
                }
                a[i] -= spl;
                last += spl / m;

                ll take = (spl + m - 1) / m;
                gaps.erase(gaps.begin());
                gaps.insert({j, ct - take});
                ans += s(m) * take;

                if (spl % m != 0) {
                    int k = j - spl % m;
                    gaps.insert({k, 1});
                    ans -= s(m - spl % m);
                }
            }
            if (last - a[i] > 1) {
                gaps.insert({i, last - a[i] - 1});
            }
            last = a[i];
        }
        cout << ans << endl;
    }
    return 0;
}
