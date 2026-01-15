//https://codeforces.com/contest/2180/problem/E
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

        ll l, r;
        cin >> l >> r;
        int n = -1;
        for (int i = 60; i >= 0; i--) {
            ll ca = (1ll << i) & l;
            if (ca) {
                ca = 1;
            }
            ll cb = (1ll << i) & r;
            if (cb) {
                cb = 1;
            }
            if (ca != cb) {
                n = i;
                break;
            }
        }
        if (n == -1) {
            cout << 0 << endl;
            continue;
        }
        ll mid = l;
        for (int i = 0; i < n; i++) {
            ll c = (1ll << i) & l;
            mid ^= c;
        }
        mid ^= (1ll << n);
        ll il = mid - l, ir = r - mid + 1;
        ll ans = 1;
        while (il % 2 == 0 && ir % 2 == 0) {
            ans *= 2;
            il /= 2, ir /= 2;
        }
        if (il == ir) {
            ans = ans * 2 - 1;
        } else {
            ans = ans - 1;
        }
        cout << ans << endl;

	}

	return 0;
}
