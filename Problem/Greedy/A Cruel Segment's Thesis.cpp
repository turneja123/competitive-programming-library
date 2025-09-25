//https://codeforces.com/contest/2140/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e10;

bool comp(pair<ll, ll> a, pair<ll, ll> b) {
    return a.first + a.second > b.first + b.second;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pair<ll, ll>> a;
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ll l, r;
            cin >> l >> r;
            ans += r - l;
            ans -= l;
            a.push_back({l, r});
        }
        if (n == 1) {
            cout << a[0].second - a[0].first << endl;
            continue;
        }

        sort(a.begin(), a.end(), comp);
        ll best = -INF;
        for (int i = 0; i < n / 2; i++) {
            ans += a[i].first + a[i].second;
            best = max(best, -a[i].second);
        }
        if (n % 2 == 0) {
            cout << ans << endl;
        } else if (n % 2 == 1) {
            ll mx = -INF;
            for (int i = n / 2; i < n; i++) {
                mx = max(mx, a[i].first);
                mx = max(mx, a[i].first + a[i].second + best);
            }
            cout << ans + mx << endl;
        }
    }
    return 0;
}
