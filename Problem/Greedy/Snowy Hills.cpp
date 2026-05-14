//https://www.codechef.com/START238A/problems/SNWHLS
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k, h;
        cin >> n >> k >> h;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        ll ans = 0;
        for (int i = 1; i < n; i++) {
            if (a[i] <= a[i - 1]) {
                ans += (ll)(a[i - 1] - a[i]) * k;
                continue;
            }
            ll x = a[i - 1], y = a[i];
            ll best = 1e18, s = 0;

            while (x < y) {
                while (1) {
                    ll lsb = x & -x;
                    if (x + lsb > y) {
                        best = min(best, s + (x + lsb - y) * k);
                        break;
                    }
                    x += lsb;
                }
                best = min(best, s + (y - x) * h);
                s += h;
                x++;
            }
            ans += best;
        }
        cout << ans << endl;

    }



    return 0;
}
