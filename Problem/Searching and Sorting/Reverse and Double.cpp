//https://codeforces.com/contest/2279/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int solve(vector<int> a, int f) {
    int n = a.size();
    if (n == 1) {
        return 0;
    }
    vector<int> d(n, 0);
    int mx = -1, pos = -1;
    for (int i = 0; i < n - 1; i++) {
        d[i] = abs(a[i] - a[i + 1]);
        if (f == 1) {
            if (d[i] > mx) {
                mx = d[i];
                pos = i;
            }
        } else {
            if (d[i] >= mx) {
                mx = d[i];
                pos = i;
            }
        }
    }
    int ans = mx;

    vector<int> pref(n, 0), suf(n, 0);
    for (int i = 0; i < n; i++) {
        pref[i] = (i == 0 ? d[i] : max(pref[i - 1], d[i]));
    }
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = (i == n - 1 ? d[i] : max(suf[i + 1], d[i]));
    }
    int cur = 0;

    for (int i = pos + 1; i < n; i++) {
        if (i != pos + 1) {
            cur = max(cur, 2 * abs(a[i - 1] - a[i]));
        }
        int lf = (pos == 0 ? 0 : pref[pos - 1]);
        int rt = (i == n - 1 ? 0 : suf[i + 1]);
        lf = max(lf, abs(2 * a[i] - a[pos]));
        if (i + 1 < n) {
            rt = max(rt, abs(2 * a[pos + 1] - a[i + 1]));
        }
        ans = min(ans, max({lf, cur, rt}));
    }
    return ans;

}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int ans = solve(a, 1);
        reverse(a.begin(), a.end());
        ans = min(ans, solve(a, 0));
        cout << ans << endl;
    }

    return 0;
}
