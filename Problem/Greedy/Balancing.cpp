//https://codeforces.com/contest/2081/problem/B
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
        int l = n, r = -1, ans = 0;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (i != 0 && a[i] < a[i - 1]) {
                l = min(l, i - 1);
                r = max(r, i);
                ans++;
            }
        }
        if (ans == 0) {
            cout << 0 << endl;
        } else if (ans % 2 == 0 && a[r] - a[l] < r - l) {
            cout << ans / 2 + 1 << endl;
        } else {
            cout << (ans + 1) / 2 << endl;
        }
    }
    return 0;
}
