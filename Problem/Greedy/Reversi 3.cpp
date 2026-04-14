//https://atcoder.jp/contests/arc216/tasks/arc216_a
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
        ll ans = 0;
        int cur = 0, ok = a[0] == b[0] && a[n - 1] == b[n - 1];
        for (int i = 1; i < n; i++) {
            cur += (i % 2 == 1 ? 1 : -1) * ((a[i] != a[i - 1]) - (b[i] != b[i - 1]));
            ans += abs(cur);
        }
        if (!ok || cur != 0) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}
