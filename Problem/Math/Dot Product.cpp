//https://atcoder.jp/contests/arc200/tasks/arc200_a
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
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        int i = 0, j = -1;
        for (int k = 1; k < n; k++) {
            int gi = __gcd(a[i], b[i]), gk = __gcd(a[k], b[k]);

            if (!(a[k] / gk == a[i] / gi && b[k] / gk == b[i] / gi)) {
                j = k;
                break;
            }
        }
        if (j == -1) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
            vector<int> ans(n, 0);
            ll s = (ll)a[i] * b[j] - (ll)a[j] * b[i];
            if (s < 0) {
                swap(i, j);
            }
            ans[i] = a[j] + b[j];
            ans[j] = -(a[i] + b[i]);
            for (int k = 0; k < n; k++) {
                cout << ans[k] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
