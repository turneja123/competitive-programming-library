//https://codeforces.com/contest/2239/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];
ll pref[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, d;
        cin >> n >> d;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < 3 * n; i++) {
            pref[i] = (i == 0 ? 0 : pref[i - 1]) + a[i % n];
        }
        ll ans = 0;
        for (int i = n; i < 2 * n; i++) {
            int l = i - d, r = i + d;
            ll s = pref[r] - pref[l - 1] - a[i % n];
            ans += max(0ll, (ll)2 * d * a[i % n] - s);
        }
        cout << ans << endl;
    }

    return 0;
}
