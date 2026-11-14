//https://codeforces.com/contest/2271/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e18;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; ll m, k;
        cin >> n >> m >> k;
        vector<ll> lefts(n), rights(n);

        vector<ll> pref(n);
        for (int i = 0; i < n; i++) {
            cin >> lefts[i] >> rights[i];
            pref[i] = (i == 0 ? 0 : pref[i - 1]) + rights[i] - lefts[i] + 1;
        }
        if (k == 0) {
            cout << INF << endl;
            continue;
        }

        auto calc = [&](ll x) -> ll {
            ll ans = 0;
            int l = upper_bound(lefts.begin(), lefts.end(), x) - lefts.begin() - 1;

            if (l != -1) {
                ans += max(0ll, min(m, rights[l] - x + 1));
                if (x + m - 1 <= rights[l]) {
                    return ans;
                }
            }
            int r = upper_bound(lefts.begin(), lefts.end(), x + m - 1) - lefts.begin() - 1;
            if (l != r) {
                ans += min(x + m - 1, rights[r]) - lefts[r] + 1;
            }

            r--;
            l++;
            if (l <= r) {
                ans += (pref[r] - (l == 0 ? 0 : pref[l - 1]));
            }
            return ans;
        };
        ll ans = -1;
        ll L = 1;
        for (int i = 0; i < n; i++) {
            ll R = lefts[i] - 1;

            ll l = L, r = R;
            while (l <= r) {
                ll mid = (l + r) / 2;
                ll cur = calc(mid);
                if (cur >= k) {
                    if (cur == k) {
                        ans = mid;
                    }
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }

            }
            l = lefts[i], r = rights[i];
            while (l <= r) {
                ll mid = (l + r) / 2;
                ll cur = calc(mid);
                if (cur >= k) {
                    if (cur == k) {
                        ans = mid;
                    }
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            L = rights[i] + 1;
        }
        cout << ans << endl;

    }
    return 0;
}
