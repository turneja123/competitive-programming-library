//https://www.codechef.com/problems/PARTSCORE
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        if (n == 2) {
            cout << 2 * a[0] + 2 * a[1] << endl;
            continue;
        }
        if (n == 3) {
            cout << a[0] + a[1] + 2 * a[2] << endl;
            continue;
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (n - i < k) {
                break;
            }
            int l = i + max(0, k - 2);
            int mn = ((i == 0) ? a[l + 1] : a[0]);
            int mx = ((l >= n - 2) ? a[i - 1] : a[n - 2]);
            ans = max(ans, mn + mx + a[i] + a[n - 1]);

        }
        cout << ans << endl;

    }
    return 0;
}
