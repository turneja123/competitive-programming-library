//https://codeforces.com/contest/2020/problem/C
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
        long long b, c, d;
        cin >> b >> c >> d;
        long long diff = d - (b - c);
        if (diff < 0) {
            cout << -1 << endl;
            continue;
        }
        int can = 1; long long ans = 0;
        for (long long k = 60; k >= 0; k--) {
            long long l = b & (1ll << k), r = c & (1ll << k), d = diff & (1ll << k);
            if (l && !r && d) {
                can = false;
            }
            if (l && r && !d) {
                ans += 1ll << k;
            }
            if (!l && r && !d) {
                can = false;
            }
            if (!l && !r && d) {
                ans += 1ll << k;
            }
        }
        if (!can) {
            ans = -1;
        }
        cout << ans << endl;
    }
    return 0;
}
