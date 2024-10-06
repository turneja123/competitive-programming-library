//https://atcoder.jp/contests/abc373/tasks/abc373_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

pair<long long, int> a[N];
long long vals[N];
long long pref[N];
long long ans[N];

int main() {
    IOS;
    int n, m; long long k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a, a + n);
    for (int i = 0; i < n; i++) {
        vals[i] = a[i].first;
        pref[i] = ((i == 0) ? vals[i] : pref[i - 1] + vals[i]);
    }
    long long sum = pref[n - 1];
    for (int i = 0; i < n; i++) {
        long long l = 0, r = k - sum, mn = -1;
        while (l <= r) {
            long long mid = (l + r) / 2;
            long long x = a[i].first + mid, rem = k - sum - mid;
            int need = m;
            int pos = upper_bound(vals, vals + n, x) - vals;
            need -= n - pos;
            if (need <= 0) {
                l = mid + 1;
                continue;
            }
            pos--;
            int lf = pos - need + 1;
            if (lf <= i) {
                lf--;
            }
            if (lf < 0) {
                r = mid - 1;
                mn = mid;
                continue;
            }
            long long diff = (x + 1) * (pos - lf + 1) - (pref[pos] - ((lf == 0) ? 0 : pref[lf - 1]));
            if (lf <= i) {
                diff -= x + 1;
                diff += vals[i];
            }
            if (diff > rem) {
                r = mid - 1;
                mn = mid;
            } else {
                l = mid + 1;
            }
        }
        ans[a[i].second] = mn;
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
