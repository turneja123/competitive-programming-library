//https://codeforces.com/contest/2140/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e10;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (i % 2 == 0) {
                ans += a[i];
            } else {
                ans -= a[i];
            }
        }
        ll best = n - 1 - (n % 2 == 0);
        ll mn = INF, mx = -INF;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 1) {
                best = max(best, 2 * a[i] + i - mn);
                mx = max(mx, 2 * a[i] - i);
            }
            if (i % 2 == 0) {
                best = max(best, - 2 * a[i] + i + mx);
                mn = min(mn, 2 * a[i] + i);
            }
        }
        cout << ans + best << endl;


    }
    return 0;
}
