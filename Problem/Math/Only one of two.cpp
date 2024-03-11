//https://atcoder.jp/contests/abc341/tasks/abc341_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    long long n, m, k;
    cin >> n >> m >> k;
    if (n > m) {
        swap(n, m);
    }
    long long l = n, r = 9e18;
    long long ans = r;
    while (l <= r) {
        long long mid = (l + r) / 2ll;
        long long g = __gcd(n, m);
        long long ct = mid / n + mid / m - 2ll * (mid / (n * m / g)) ;
        if (ct < k) {
            l = mid + 1;
        } else {
            if (mid % n == 0 || mid % m == 0) {
                ans = min(ans, mid);
            }
            r = mid - 1;
        }
    }
    cout << ans << endl;

    return 0;
}
