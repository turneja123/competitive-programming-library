//https://codeforces.com/contest/2119/problem/C
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
        ll n, l, r, k;
        cin >> n >> l >> r >> k;
        if (n % 2 == 1) {
            cout << l << endl;
        } else {
            ll p = 1;
            while (p <= l) {
                p *= 2;
            }
            if (p > r || n == 2) {
                cout << -1 << endl;
                continue;
            }
            if (k <= n - 2) {
                cout << l << endl;
            } else {
                cout << p << endl;
            }

        }
    }

    return 0;
}
