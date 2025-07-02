//https://www.wincentdragonbyte.com/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;


long long Sqrt(long long n) {
    long long l = 1, r = 3e9, ans;
    while (l <= r) {
        long long mid = (l + r) / 2;
        if (mid * mid <= n) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int main() {
    IOS;
    freopen("B3.in", "r", stdin);
    freopen("N1.out", "w", stdout);
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        if (n == 1) {
            cout << 3 << endl;
            continue;
        }
        if (n == 2) {
            cout << -1 << endl;
            continue;
        }
        if (n == 3) {
            cout << 3 << endl;
            continue;
        }
        long long ans = n - 1;
        for (int i = 3; i <= min(n - 1, 1000000ll); i++) {
            long long t = n;
            int can = 1;
            while (t > 0) {
                if (t % i > 1) {
                    can = 0;
                    break;
                }
                t /= i;
            }
            if (can) {
                ans = i;
                break;
            }
        }
        if (n < 1000000) {
            cout << ans << endl;
            continue;
        }
        long long x = Sqrt(n);
        if (x * x == n) {
            ans = min(ans, x);
        }
        x = Sqrt(n - 1);
        if (x * x == n - 1) {
            ans = min(ans, x);
        }
        x = Sqrt(4 * n + 1);
        if (x * x == 4 * n + 1) {
            x -= 1;
            if (x % 2 == 0) {
                x /= 2;
                ans = min(ans, x);
            }
        }
        x = Sqrt(4 * n - 3);
        if (x * x == 4 * n - 3) {
            x -= 1;
            if (x % 2 == 0) {
                x /= 2;
                ans = min(ans, x);
            }
        }

        cout << ans << endl;
    }
    return 0;
}

