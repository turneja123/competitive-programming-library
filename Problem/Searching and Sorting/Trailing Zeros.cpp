//https://www.spoj.com/problems/ALIEN0/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int pref[N][3];

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int a, ct = 0;
        cin >> a;
        while (a % 2 == 0) {
            ct++;
            a /= 2;
        }
        pref[i][0] = pref[i - 1][0] + ct, ct = 0;
        while (a % 3 == 0) {
            ct++;
            a /= 3;
        }
        pref[i][1] = pref[i - 1][1] + ct, ct = 0;
        while (a % 5 == 0) {
            ct++;
            a /= 5;
        }
        pref[i][2] = pref[i - 1][2] + ct, ct = 0;
    }
    for (int i = 0; i < q; i++) {
        int l, r, s, ans;
        cin >> l >> r >> s;
        if (s == 2) {
            ans = pref[r][0] - pref[l - 1][0];
        } else if (s == 3) {
            ans = pref[r][1] - pref[l - 1][1];
        } else if (s == 4) {
            ans = (pref[r][0] - pref[l - 1][0]) / 2;
        } else if (s == 5) {
            ans = pref[r][2] - pref[l - 1][2];
        } else {
            ans = min(pref[r][0] - pref[l - 1][0], pref[r][1] - pref[l - 1][1]);
        }
        cout << ans << endl;
    }

    return 0;
}
