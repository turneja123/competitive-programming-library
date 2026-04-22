//https://codeforces.com/contest/2215/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


const int N = 1e5 + 5;

int a[N];
ll pref[N][3];


ll get(int l, int r, int m) {
    if (l > r) {
        return 0;
    }
    return pref[r][m] - (l == 0 ? 0 : pref[l - 1][m]);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k, p, q;
        cin >> n >> k >> p >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            pref[i][0] = a[i] % p % q;
            pref[i][1] = a[i] % q % p;
            pref[i][2] = min(pref[i][0], pref[i][1]);
            if (i != 0) {
                pref[i][0] += pref[i - 1][0];
                pref[i][1] += pref[i - 1][1];
                pref[i][2] += pref[i - 1][2];
            }
        }
        ll ans = 1e18;
        for (int i = 0; i < n - k + 1; i++) {
            ans = min(ans, min(get(i, i + k - 1, 0), get(i, i + k - 1, 1)) + get(0, i - 1, 2) + get(i + k, n - 1, 2));
        }
        cout << ans << endl;

    }
    return 0;
}
