//https://codeforces.com/contest/2021/problem/A
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
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        int l = 1, r = a[n - 1], ans = 1;
        while (l <= r) {
            int mid = (l + r) / 2, need = mid;
            for (int i = n - 1; i > 0; i--) {
                if (need > a[i]) {
                    break;
                }
                need = max(0, 2 * need - a[i]);
            }
            if (need <= a[0]) {
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
