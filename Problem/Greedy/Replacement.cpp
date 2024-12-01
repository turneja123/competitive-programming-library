//https://codeforces.com/contest/2029/problem/B
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
        int n;
        cin >> n;
        string a, b;
        cin >> a >> b;
        string ans = "YES";
        int x = 0, y = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == '1') {
                x++;
            } else {
                y++;
            }
        }
        for (int i = 0; i < n - 1; i++) {
            x--, y--;
            if (x < 0 || y < 0) {
                ans = "NO";
                break;
            }
            if (b[i] == '1') {
                x++;
            } else {
                y++;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
