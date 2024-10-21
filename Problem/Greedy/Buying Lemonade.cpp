//https://codeforces.com/contest/2024/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; long long k;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        long long ans = 0; long long diff = 0;
        for (int i = 0; i < n; i++) {
            if (k > 0 && i > 0) {
                ans++;
            }
            a[i] = a[i] - diff;
            if (a[i] * (n - i) > k) {
                ans += k;
                k = 0;
            } else {
                ans += a[i] * (n - i);
                k -= a[i] * (n - i);
            }
            diff += a[i];
        }
        cout << ans << endl;
    }

    return 0;
}
