//https://codeforces.com/contest/2008/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
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
        if (n == 1) {
            if (a[0] >= k) {
                cout << k - 1 << endl;
            } else {
                cout << k << endl;
            }
            continue;
        }
        int g = a[0];
        for (int i = 1; i < n; i++) {
            g = __gcd(g, a[i]);
        }
        if (g == 1) {
            cout << n - 1 + k << endl;
        } else {
            long long ct = (long long)(g - 1) * (n - 1);
            if (ct >= k) {
                int ans = ((k - 1) / (g - 1)) * g + (k - 1) % (g - 1) + 1;
                cout << ans << endl;
            } else {
                k -= ct;
                cout << g * (n - 1) + k << endl;
            }
        }
    }
    return 0;
}
