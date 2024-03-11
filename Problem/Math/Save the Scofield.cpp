//https://www.spoj.com/problems/UJ01/
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
        long long n, a, b;
        cin >> a >> b >> n;
        if (a > b) {
            swap(a, b);
        }
        long long l = 1, r = n * a * b, ans = 1;
        while (l <= r) {
            long long mid = (l + r) / 2;
            long long ct = mid / a + mid / b - mid / (a * b / __gcd(a, b));
            if (ct <= n) {
                ans = max(ans, max(mid - mid % a, mid - mid % b));
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
