//https://qoj.ac/contest/2539/problem/14428
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
        ll h, w, s;
        cin >> h >> w >> s;
        ll ans = h * w;
        ll x = 1;
        while (x <= h) {
            ll a = (h + x - 1) / x;
            if (s >= a && w >= (w + s / a - 1) / (s / a)) {
                ans = min(ans, (w + s / a - 1) / (s / a) + x - 2);
            }
            if (a == 1) {
                break;
            }
            x = (h - 1) / (a - 1) + 1;
        }
        cout << ans <<endl;
    }
    return 0;
}
