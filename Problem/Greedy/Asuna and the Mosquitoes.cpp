//https://codeforces.com/contest/2092/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int ct = 0;
        int mx = 0;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            mx = max(mx, a);
            ct += a % 2;
            ans += a;
        }
        if (ct == n || ct == 0) {
            cout << mx << endl;
            continue;
        }
        ct--;
        cout << ans - ct << endl;
    }

    return 0;
}
