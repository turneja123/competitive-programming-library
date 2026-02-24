//https://atcoder.jp/contests/arc215/tasks/arc215_a
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
        int n, k, m;
        cin >> n >> k >> m;
        vector<int> a(n), diff;
        for (int i = 0; i < n; i++) {
            cin >> a[i];

        }
        sort(a.begin(), a.end());
        int l = a[0], r = m - a.back();
        for (int i = 1; i < n; i++) {
            diff.push_back(a[i] - a[i - 1]);
        }
        if (diff.size()) {
            sort(diff.begin(), diff.end(), greater<int>());
        }
        ll ans = max(l, r) + (ll)(k - 1) * (l + r), cur = 0;
        for (int i = 0; i < n - 1 && i + 1 <= k; i++) {
            cur += diff[i] / 2;
            l += diff[i] / 2, r += diff[i] / 2;

            ll add = 0;
            if (i + 1 < k) {
                add += max(l, r);
            }
            if (i + 2 < k) {
                add += (ll)(k - (i + 2)) * (l + r);
            }
            ans = max(ans, cur + add);
        }
        cout << ans << endl;
    }

    return 0;
}
