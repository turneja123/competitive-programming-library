//https://www.codechef.com/START221A/problems/LMP8H
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

vector<ll> pref[3];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        string a, b, c;
        cin >> n >> a >> b >> c;
        for (int i = 0; i < 3; i++) {
            pref[i].clear();
            pref[i].resize(n + 1);
        }
        int l = 0, r = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == '0') {
                l += b[i] - c[i];
            } else {
                r += b[i] - c[i];
            }
            pref[0][i + 1] = l, pref[1][i + 1] = r, pref[2][i + 1] = l + r;
        }
        ll ans = 0;
        for (int j = 0; j < 3; j++) {
            sort(pref[j].begin(), pref[j].end());
            for (int i = 0; i <= n; i++) {
                ans += pref[j][i] * (2 * i - n);
            }
        }
        cout << ans / 2 << endl;


    }
    return 0;
}
