//https://www.spoj.com/problems/KOPC12A/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N], c[N];

long long calc(int k, int n) {
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (ll)c[i] * abs(a[i] - k);
    }
    return ans;
}

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
        for (int i = 0; i < n; i++) {
            cin >> c[i];
        }
        int l = 0, r = 1e4;
        while (r - l >= 3) {
            int m1 = l + (r - l) / 3;
            int m2 = r - (r - l) / 3;

            long long f1 = -calc(m1, n);
            long long f2 = -calc(m2, n);

            if (f1 < f2) {
                l = m1 + 1;
            } else {
                r = m2 - 1;
            }
        }
        long long ans = 1e18;
        for (; l <= r; l++) {
            ans = min(ans, calc(l, n));
        }
        cout << ans << endl;
    }
    return 0;
}
