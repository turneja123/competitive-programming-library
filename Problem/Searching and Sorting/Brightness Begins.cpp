//https://codeforces.com/contest/2020/problem/B
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
        long long n;
        cin >> n;
        long long l = 1, r = 2e18, ans = 1;
        while (l <= r) {
            long long mid = (l + r) / 2;
            long long ct = mid - (long long)sqrtl(mid);
            if (ct < n) {
                l = mid + 1;
            } else {
                if (ct == n) {
                    ans = mid;
                }
                r = mid - 1;
            }
        }
        cout << ans << endl;

    }
    return 0;
}
