//https://codeforces.com/contest/1994/problem/E
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
        vector<int> f(25, 0);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            ans |= k;
            for (int j = 0; j < 25; j++) {
                int c = (1 << j) & k;
                if (c) {
                    f[j]++;
                }
            }
            for (int j = 0; j < k - 1; j++) {
                int x;
                cin >> x;
            }
        }
        for (int i = 0; i < 25; i++) {
            if (f[i] > 1) {
                ans |= (1 << i) - 1;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
