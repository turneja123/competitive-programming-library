//https://www.codechef.com/problems/EQXY
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
        int x, y, z, c;
        cin >> x >> y >> z >> c;
        if (x == y) {
            cout << 0 << endl;
            continue;
        }
        if (x > y) {
            swap(x, y);
        }
        int ans = 2 * c;
        if (y % x == 0) {
            int a = y / x;
            for (int i = 1; i <= sqrt(a); i++) {
                if (a % i == 0) {
                    ans = min(ans, c + abs(z - x * i));
                    ans = min(ans, c + abs(z - x * (a / i)));
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
