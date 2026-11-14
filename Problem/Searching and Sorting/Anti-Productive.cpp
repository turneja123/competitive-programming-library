//https://codeforces.com/contest/2279/problem/C
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
        int n, x;
        cin >> n >> x;
        vector<int> a(n);
        vector<ll> pref(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            pref[i] = (i == 0 ? 0 : pref[i - 1]) + a[i];
        }

        vector<int> lf;
        for (int i = 1; (ll)i * i < x; i++) {
            lf.push_back(i);
        }
        ll ans = pref[n - 2];
        int l = 0;
        for (int d : lf) {

            int mx = x / d;
            if (mx * d == x) {
                mx--;
            }
            while (l < n - 1 && a[l] <= d) {
                l++;
            }
            ans = min(ans, max(0, a.back() - mx) + pref[n - 2] - (l == 0 ? 0 : pref[l - 1]) - (ll)(n - 1 - l) * d);
        }
        cout << ans << endl;
    }

    return 0;
}
