//https://codeforces.com/contest/2024/problem/A
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
        long long a, b;
        cin >> a >> b;
        long long l = 0, r = a, ans = 0;
        while (l <= r) {
            long long mid = (l + r) / 2;
            long long has = a - mid, need = b - mid * 2;
            if (has >= need) {
                ans = has;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
