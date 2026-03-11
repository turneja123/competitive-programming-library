//https://codeforces.com/contest/2207/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;

int val[N][N];
ll pref[N][N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, h;
        cin >> n >> h;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            int cur = h - a[i];
            for (int j = i; j < n; j++) {
                cur = min(cur, h - a[j]);
                val[i][j] = cur;
            }
            cur = h - a[i];
            for (int j = i; j >= 0; j--) {
                cur = min(cur, h - a[j]);
                val[i][j] = cur;
            }
            for (int j = 0; j < n; j++) {
                pref[i][j] = (j == 0 ? 0 : pref[i][j - 1]) + val[i][j];
            }
        }
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, (ll)val[i][i]);
            for (int j = i + 1; j < n; j++) {
                int l = i, r = j, spl = l;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    if (val[i][mid] >= val[j][mid]) {
                        spl = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                ans = max(ans, pref[i][spl] + pref[j][n - 1] - pref[j][spl]);
            }
        }
        cout << ans << endl;

    }


    return 0;
}
