//https://codeforces.com/contest/2070/problem/C
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
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int l = 0, r = 1e9, ans = r;
        while (l <= r) {
            int mid = (l + r) / 2;

            int ct = 0;
            bool open = false;
            for (int i = 0; i < n; i++) {
                if (a[i] > mid && s[i] == 'B') {
                    if (!open) {
                        open = true;
                        ct++;
                    }
                }
                if (a[i] > mid && s[i] == 'R') {
                    if (open) {
                        open = false;
                    }
                }
            }
            if (ct <= k) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;

    }
    return 0;
}
