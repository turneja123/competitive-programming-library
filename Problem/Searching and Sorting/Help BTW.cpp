//https://www.spoj.com/problems/HELPBTW/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

long long a[N];
long long pref[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, k; long long mn = 2e9;
        cin >> n >> m >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mn = min(mn, a[i]);
        }
        if (k == 0 || m == 0) {
            cout << mn << endl;
            continue;
        }
        long long l = mn + 1, r = 2e9, ans = mn;
        while (l <= r) {
            long long mid = (l + r) / 2, sum = 0, ops = k;
            bool flag = true;
            for (int i = 0; i < n && flag; i++) {
                sum += pref[i];
                long long diff = mid - (a[i] + sum);
                if (diff > ops) {
                    flag = false;
                } else if (diff > 0) {
                    sum += diff;
                    ops -= diff;
                    if (i + m < n) {
                        pref[i + m] -= diff;
                    }
                }
            }
            if (flag) {
                ans = max(ans, mid);
                l = mid + 1;
            } else {
                r = mid - 1;
            }
            for (int i = 0; i < n; i++) {
                pref[i] = 0;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
