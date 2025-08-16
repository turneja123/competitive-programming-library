//https://www.codechef.com/problems/EVCOST
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = double;

const int N = 2e5 + 5;

ld dp[N];
int a[N];
int b[N];

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(9);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        dp[n] = 0;
        ld l = 1.0, r = 1e18;
        for (int it = 0; it < 200; it++) {
            ld mid = (l + r) / 2;
            ld s = 0;
            for (int i = n - 1; i >= 0; i--) {
                dp[i] = min(dp[i + 1] + a[i], mid + b[i]);
                s += dp[i];
            }
            s /= (ld)(n + 1);
            if (s < mid) {
                r = mid;
            } else {
                l = mid;
            }
        }
        cout << dp[0] << endl;
    }
    return 0;
}
