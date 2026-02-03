//https://codeforces.com/contest/2187/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9 + 5;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        int mn = INF, mx = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            mn = min(mn, a[i]), mx =  max(mx, a[i]);
        }
        vector<int> b = a;
        sort(b.begin(), b.end());
        if (a == b) {
            cout << -1 << endl;
            continue;
        }
        int l = 0, r = INF, ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            int ok = 1;
            for (int i = 0; i < n; i++) {
                if (a[i] != b[i] && max(a[i] - mn, mx - a[i]) < mid) {
                    ok = 0;
                }
            }
            if (ok) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << ans << endl;
    }


    return 0;
}
