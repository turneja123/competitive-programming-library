//https://qoj.ac/contest/1452/problem/7944
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        int mn = INF, mx = -INF;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mn = min(mn, a[i]);
            mx = max(mx, a[i]);
        }
        int ans = mx - mn;
        int l = mn, r = mx;
        while (l <= r) {
            int mid = (l + r) / 2;
            int lf = n, rt = -1;
            for (int i = 0; i < n; i++) {
                if (a[i] < mid) {
                    lf = min(lf, i);
                    rt = max(rt, i);
                }
            }
            int s = -INF;
            for (int i = lf; i <= rt; i++) {
                s = max(s, a[i]);
            }
            if (mx - s >= mid - mn) {
                ans = min(ans, mx - mid);
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        l = mn, r = mx;
        while (l <= r) {
            int mid = (l + r) / 2;
            int lf = n, rt = -1;
            for (int i = 0; i < n; i++) {
                if (a[i] > mid) {
                    lf = min(lf, i);
                    rt = max(rt, i);
                }
            }
            int s = INF;
            for (int i = lf; i <= rt; i++) {
                s = min(s, a[i]);
            }
            if (s - mn >= mx - mid) {
                ans = min(ans, mid - mn);
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
