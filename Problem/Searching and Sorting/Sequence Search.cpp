//https://www.codechef.com/problems/SEQSEARCH
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long s[100];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long k;
        cin >> s[1] >> s[2] >> k;
        s[0] = 0;
        /*cout << s[0] << " " << s[1] << " " << s[2] << " ";
        for (int i = 3; i < 20; i++) {
            s[i] = s[i - 1] + s[i - 2] - s[i - 3];
            cout << s[i] << " ";
        }
        cout << endl;*/
        long long l = 0, r = 3e18, ans = 0;
        while (l <= r) {
            long long mid = (l + r) / 2;
            long long x = mid / s[2] + 1, y = max(0ll, (mid - s[1]) / s[2]) + (mid >= s[1]);
            if (x + y >= k) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
    }


    return 0;
}
