//https://atcoder.jp/contests/arc201/tasks/arc201_a
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
        int n;
        cin >> n;
        ll suma = 0, sumb = 0, diff = 0;
        for (int i = 0; i < n; i++) {
            int a, b, c;
            cin >> a >> c >> b;
            a = min(a, c), b = min(b, c);
            suma += a, sumb += b;
            if (a + b > c) {
                diff += a + b - c;
            }
        }
        ll l = 1, r = min(suma, sumb), ans = 0;
        while (l <= r) {
            ll mid = (l + r) / 2;
            if (suma + sumb - 2 * mid >= diff) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << ans << endl;


    }
    return 0;
}
