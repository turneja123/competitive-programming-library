//https://eolymp.com/en/problems/12267
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n == 1) {
            cout << "? 1 1" << endl;
            int x;
            cin >> x >> x;
            cout << "! " << 67 - x << endl;
        } else if (n == 2) {
            cout << "? 1 1" << endl;
            int x;
            cin >> x >> x;
            cout << "? 1 2" << endl;
            int y;
            cin >> y >> y;
            int z = x * 10 + y;
            int ans;
            if (z < 67) {
                ans = 67 - z;
            } else {
                ans = 167 - z;
            }
            cout << "! " << ans << endl;

        } else {
            cout << "? 1 " << n - 1 << endl;
            int x;
            cin >> x >> x;
            cout << "? 1 " << n << endl;
            int y;
            cin >> y >> y;
            int z = x * 10 + y;
            int ans;
            if (z < 67) {
                ans = 67 - z;
            } else {
                ans = 167 - z;
            }
            cout << "? 1 " << n - 2 << endl;
            int p;
            cin >> p >> p;
            if (p == 6 && x == 6) {
                ans = min(ans, 10 - y);
            }
            if (p == 6 && n > 3) {
                cout << "? 1 " << n - 3 << endl;
                int q;
                cin >> q >> q;
                if (q == 6) {
                    ans = min(ans, 100 - z);
                }
            }
            if (p == 9) {
                int l = 1, r = n - 2, spl = r;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    cout << "? " << n - 2 - mid + 1 << " ";
                    for (int i = mid; i <= n - 2; i++) {
                        cout << i << " ";
                    }
                    cout << endl;
                    int s, q;
                    cin >> s;
                    for (int i = 0; i < s; i++) {
                        cin >> q;
                    }
                    if (s > 1) {
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                        spl = mid;
                    }
                }
                if (spl > 2) {
                    cout << "? 1 " << spl - 2 << endl;
                    int x;
                    cin >> x >> x;
                    cout << "? 1 " << spl - 1 << endl;
                    int y;
                    cin >> y >> y;
                    if (x == 6 && y == 6) {
                        ans = min(ans, 100 - z);
                    }
                }
            }
            cout << "! " << ans << endl;
        }
    }

    return 0;
}
