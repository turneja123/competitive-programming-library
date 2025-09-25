//https://www.codechef.com/problems/PREFSUFREC
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
        vector<int> f(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> f[i];
        }
        int can = 1;
        for (int i = n; i > 0; i--) {
            if (f[i]) {
                if (f[i] == 1) {
                    can = 0;
                }
                break;
            }
        }
        if (!can) {
            cout << -1 << endl;
            continue;
        }

        vector<int> ans(n);
        ans[n - 1] = 1;
        f[1] -= n;
        int j = 1;
        for (int i = 0; i < n - 1; i++) {
            while (f[j] == 0) {
                j++;
            }
            f[j]--;
            ans[i] = j;
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
