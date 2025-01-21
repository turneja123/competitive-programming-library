//https://codeforces.com/contest/2057/problem/C
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
        int l, r;
        cin >> l >> r;
        int k = 29;
        int a = 0, b = 0, c = 0;
        while (1) {
            int cl = l & (1 << k);
            int cr = r & (1 << k);
            if (cr != 0 && cl == 0) {
                break;
            }
            if (cl) {
                a += 1 << k;
            }
            k--;
        }
        b = a + (1 << k);
        c = a + (1 << k) - 1;
        if (b + 1 <= r) {
            a = b + 1;
        } else {
            a = c - 1;
        }
        cout << a << " " << b << " " << c << endl;
    }
    return 0;
}
