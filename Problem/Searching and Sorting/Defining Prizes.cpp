//https://www.facebook.com/codingcompetitions/hacker-cup/2025/round-2/problems/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    //freopen("248.in", "r", stdin);
    //freopen("248.out", "w", stdout);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        vector<int> b(m);
        vector<ll> pref(m, 0);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < m; i++) {
            cin >> b[i];
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        for (int i = 0; i < m; i++) {
            pref[i] = (i == 0 ? 0 : pref[i - 1]) + b[i];
        }
        vector<int> v;
        int last = a[0], ct = 1;
        for (int i = 1; i < n; i++) {
            if (a[i] != last) {
                v.push_back(ct);
                last = a[i];
                ct = 1;
            } else {
                ct++;
            }
        }
        v.push_back(ct);
        int z = v.size();
        int l = 0, r = z - 1, ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            int can = 1;
            ll s = 0; int norm_s = 0;
            for (int i = z - 1; i >= mid; i--) {
                norm_s += v[i];
                s = s + norm_s;
                int j = i - mid + 1;
                if (j > m) {
                    can = 0;
                    break;
                }
                if (pref[m - j] < s) {
                    can = 0;
                    break;
                }
            }
            if (can) {
                ans = norm_s;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        cout << "Case #" << tt << ": " << ans << endl;

    }
    return 0;
}
