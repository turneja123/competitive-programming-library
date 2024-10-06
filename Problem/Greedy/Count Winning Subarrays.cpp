//https://www.codechef.com/problems/COUNTWINSUB?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        long long ans = a[0]; int l = -1;
        for (int i = 1; i < n; i++) {
            if (a[i] == 1 && a[i] == a[i - 1]) {
                l = i - 1;
            }
            if (i > 1 && a[i] == 1 && a[i - 2] == 1) {
                l = max(l, i - 2);
            }
            if (l != -1) {
                ans += l + 1;
            }
            if (a[i] == 1) {
                ans++;
            }
        }
        cout << ans << endl;

    }

    return 0;
}
