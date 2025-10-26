//https://tlx.toki.id/problems/troc-39/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

ll a[N];

ll calc(int i, int x, int y) {
    ll ans = -(a[i] * a[i - 1] + a[i + 1] * a[i] + a[i + 2] * a[i + 1]);
    a[i] += x;
    a[i + 1] += y;
    ans += a[i] * a[i - 1] + a[i + 1] * a[i] + a[i + 2] * a[i + 1];
    a[i] -= x;
    a[i + 1] -= y;
    return ans;
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ans += a[i] * a[i - 1];
    }
    ll best = 0;
    for (int i = 1; i <= n - 1; i++) {
        int l = 0, r = k;
        while (r - l >= 3) {
            int m1 = l + (r - l) / 3;
            int m2 = r - (r - l) / 3;

            ll f1 = calc(i, m1, k - m1);
            ll f2 = calc(i, m2, k - m2);

            if (f1 < f2) {
                l = m1 + 1;
            } else {
                r = m2 - 1;
            }
        }

        for (; l <= r; l++) {
            best = max(best, calc(i, l, k - l));
        }
    }
    cout << ans + best;

    return 0;
}
