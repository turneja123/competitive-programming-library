//https://atcoder.jp/contests/arc197/tasks/arc197_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

const int N = 2e5 + 5;
const ld eps = 1e-18;

ll a[N];
ll pref[N];

ld calc(int r, ll s, int n) {
    return ((ld)s + (ld)pref[r]) / (ld)(n + r + 1);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        for (int i = 0; i < n; i++) {
            pref[i] = ((i == 0) ? 0 : pref[i - 1]) + a[i];
        }
        int ans = 0;
        for (int i = 1; i < n; i++) {

            int L = i, R = n - 1, spl = -1;
            while (L <= R) {
                int mid = (L + R) / 2;
                ll s = pref[mid] - pref[i - 1];
                int l = 0, r = i - 1;
                while (r - l >= 3) {
                    int m1 = l + (r - l) / 3;
                    int m2 = r - (r - l) / 3;

                    ld f1 = -calc(m1, s, mid - i + 1);
                    ld f2 = -calc(m2, s, mid - i + 1);

                    if (f1 < f2) {
                        l = m1 + 1;
                    } else {
                        r = m2 - 1;
                    }
                }
                ld cur = 1e18;
                for (; l <= r; l++) {
                    cur = min(cur, calc(l, s, mid - i + 1));
                }
                if ((ld)a[i] > cur) {
                    spl = mid;
                    L = mid + 1;
                } else {
                    R = mid - 1;
                }
            }
            ans = max(ans, spl - i + 1);
        }
        cout << ans << endl;
    }
    return 0;
}
