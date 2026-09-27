//https://atcoder.jp/contests/arc229/tasks/arc229_b
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
        vector<int> a(n);
        int ok = 1;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            if (i != 0 && 2 * a[i] > a[i - 1]) {
                ok = 0;
                break;
            }
        }
        if (!ok) {
            cout << -1 << endl;
            continue;
        }
        ll ans = 0;
        if (a[n - 1] != 0) {
            int cur = a[n - 1];
            a[n - 1] = 0;
            for (int i = n - 2; i >= 0; i--) {
                if (a[i] - (2 * cur + 1) >= 2 * a[i + 1]) {
                    cur = 2 * cur + 1;
                } else {
                    cur = 2 * cur;
                }
                a[i] -= cur;
            }
            ans++;
        }
        while (1) {
            int f = -1;
            for (int i = n - 1; i >= 0; i--) {
                if (a[i] > 0) {
                    f = i;
                    break;
                }
            }
            if (f == -1) {
                break;
            }
            int ct = a[f], cur = a[f];
            ans += cur;
            a[f] -= cur;
            for (int i = f - 1; i >= 0; i--) {
                cur *= 2;
                int add = min(ct, a[i] - cur - 2 * a[i + 1]);
                cur += add;
                a[i] -= cur;
            }
        }

        cout << ans << endl;
    }
    return 0;
}
