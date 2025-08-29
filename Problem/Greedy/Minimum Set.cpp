//https://www.codechef.com/START200A/problems/MINSET
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
        ll n;
        cin >> n;
        ll ans = 0, pw = 1;
        for (int i = 1; i <= 30; i++) {
            ans += (n - 1) / (pw * 2) * pw;
            pw *= 2;
        }
        if (n % 2 == 0) {
            ans += n & -n;
            if (__builtin_popcount(n) != 1) {
                ans--;
            }
        }
        cout << ans + n - 1 << endl;
    }

    return 0;
}
