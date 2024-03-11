#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 205;

ll a[N];
ll vals[N][N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (ll i = 0; i < n; i++) {
        ll cur = 0;
        for (ll j = 0; j <= i; j++) {
            cur += a[j];
        }
        int l = 0;
        vals[i][l] = cur / (i + 1);
        for (ll j = i + 1; j < n; j++) {
            cur -= a[l++];
            cur += a[j];
            vals[i][l] = cur / (i + 1);
        }
    }
    for (int i = 0; i < n; i++) {
        sort(vals[i], vals[i] + n - i);
    }
    int q;
    cin >> q;
    while (q--) {
        int l, r, wt;
        cin >> l >> r >> wt;
        l--, r--;
        int ans = 0;
        for (int i = l; i <= r; i++) {
            ans += n - i - (int)(lower_bound(vals[i], vals[i] + n - i, wt) - vals[i]);
        }
        cout << ans << endl;
    }
    return 0;
}
