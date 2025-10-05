//https://codeforces.com/contest/2152/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int pref[N];
int a[N];
int z[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            pref[i] = (i == 0 ? 0 : pref[i - 1]) + a[i];
            z[i] = (i == 0 ? 0 : z[i - 1]) + (i == 0 ? 0 : a[i] == a[i - 1]);
        }
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            int ct = pref[r] - (l == 0 ? 0 : pref[l - 1]);
            if ((r - l + 1) % 3 == 0 && ct % 3 == 0 && (r - l + 1 - ct) % 3 == 0) {
                int ans = (r - l + 1) / 3 + (z[r] == z[l]);
                cout << ans << endl;
            } else {

                cout << -1 << endl;
            }
        }
    }
    return 0;
}
