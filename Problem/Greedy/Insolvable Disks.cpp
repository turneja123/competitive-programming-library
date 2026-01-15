//https://codeforces.com/contest/2180/problem/D
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
        vector<int> d(n);
        for (int i = 0; i < n; i++) {
            cin >> d[i];
        }
        if (n == 1) {
            cout << 0 << endl;
            continue;
        }
        int x = d[1] - d[0];
        int ans = 1;
        int l = 0, r = x;
        for (int i = 2; i < n; i++) {
            int x = d[i] - d[i - 1];

            int l_nx = x - r, r_nx = x - l;
            l_nx = max(0, l_nx);
            if (r_nx <= 0) {
                l = 0, r = x;
            } else {
                ans++;
                l = l_nx;
                r = r_nx;
            }

        }
        cout << ans << endl;

    }
    return 0;
}
