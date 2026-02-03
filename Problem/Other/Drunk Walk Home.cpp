//https://ocpc2026w.eolymp.space/en/compete/mi9vnankul3g72sfvkn0heloj8/problem/4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll unsigned long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    int t;
    cin >> t;
    while (t--) {
        ld x;
        cin >> x;
        if (x >= 20) {
            ld ans = 2.0 * x + (ld)2.0 / 3.0;
            cout << ans << endl;
        } else {
            ld ans = 0, fact = 1.0;
            for (int i = 0; i <= x; i++) {
                ans += (ld)(i % 2 == 0 ? 1.0 : -1.0) * expl(x - i) * powl(x - i, i) / fact;
                fact *= (ld)(i + 1);
            }
            cout << ans << endl;
        }
    }


    return 0;
}
