//https://tlx.toki.id/contests/troc-42/problems/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    //IOS;
    int n;
    cin >> n;
    cout << "? 1 " << n << endl;
    int x;
    cin >> x;
    int bit;
    for (int i = 0; i < 20; i++) {
        int c = (1 << i) & x;
        if (c) {
            bit = i;
            break;
        }
    }
    int l = 1, r = n - 1, spl = 1, y = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        cout << "? 1 " << mid << endl;
        int x;
        cin >> x;
        int c = (1 << bit) & x;
        if (c == 0) {
            y = x;
            spl = mid + 1;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    int z = 0;
    if (spl != n) {
        cout << "? " << spl + 1 << " " << n << endl;
        cin >> z;
    }
    z |= y;
    int bit_rem;
    for (int i = 0; i < 20; i++) {
        int c = (1 << i) & z;
        if (c) {
            bit_rem = i;
            break;
        }
    }
    ll ans = 1ll << (bit + bit_rem);
    cout << "! " << ans;


    return 0;
}
