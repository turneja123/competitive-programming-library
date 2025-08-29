//https://codeforces.com/contest/2128/problem/E1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int a[N];
int b[N];
int pref[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        int l = 1, r = n, ans = 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            for (int i = 1; i <= n; i++) {
                if (a[i] >= mid) {
                    b[i] = 1;
                } else {
                    b[i] = -1;
                }
            }
            int mn = N, best = -N, cur = 0;
            for (int i = 1, l = 0; i <= n; i++) {
                while (i - l >= k) {
                    mn = min(mn, pref[l]);
                    l++;
                }
                cur += b[i];
                pref[i] = cur;
                best = max(best, cur - mn);
            }
            if (best >= 0) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }

        }
        for (int i = 1; i <= n; i++) {
            if (a[i] >= ans) {
                b[i] = 1;
            } else {
                b[i] = -1;
            }
        }
        pair<int, int> ival;
        int cur = 0;
        set<pair<int, int>> st;
        for (int i = 1, l = 0; i <= n; i++) {
            while (i - l >= k) {
                st.insert({pref[l], l});
                l++;
            }
            cur += b[i];
            pref[i] = cur;
            if (st.size()) {
                pair<int, int> p = {cur, N};
                auto it = st.upper_bound(p);
                if (it != st.begin()) {
                    --it;
                   ival.first = it->second + 1;
                   ival.second = i;
                   break;
                }
            }
        }
        cout << ans << " " << ival.first << " " << ival.second << endl;
    }
    return 0;
}
