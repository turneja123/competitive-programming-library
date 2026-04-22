//https://repovive.com/contests/5/problems/E
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
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        int ans = a.back() - a[0];

        for (int i = 1; i <= a.back(); i++) {
            ll need = 0;
            int mn = a[0];
            int j = 0;

            while (j != n) {
                int moves = (a[j] + i - 1) / i - 1;
                int l = j, r = n - 1, nx = j;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    if ((a[mid] + i - 1) / i - 1 == moves) {
                        nx = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                need += (ll)moves * (nx - j + 1);
                mn = min(mn, a[j] / (moves + 1));
                j = nx + 1;
            }
            if (need <= k) {
                ans = min(ans, i - mn);
            }
        }
        cout << ans << endl;

    }
    return 0;
}
