//https://codeforces.com/contest/1972/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; long long k, ans = 1;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
        }
        long long l = 0, r = 1e13;
        while (l <= r) {
            long long mid = (l + r) / 2, cur = k;
            for (int i = 0; i < n; i++) {
                cur -= max(0ll, mid - a[i]);
            }
            if (cur < 0) {
                r = mid - 1;
            } else {
                long long lo = 0, hi = 0;
                for (int i = 0; i < n; i++) {
                    if (a[i] <= mid) {
                        if (cur > 0) {
                            cur--;
                            hi++;
                        } else {
                            lo++;
                        }
                    } else {
                        hi++;
                    }
                }
                ans = max(ans, lo * mid + hi * (mid + 1) + 1);
                l = mid + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
