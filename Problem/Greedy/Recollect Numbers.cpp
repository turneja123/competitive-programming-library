//https://codeforces.com/contest/2201/problem/B
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
        int n, k;
        cin >> n >> k;
        int need = k - n;
        if (need < 0 || need >= n) {
            cout << "NO" << endl;
            continue;
        }
        cout << "YES" << endl;
        if (need == 0) {
            for (int i = 0; i < n; i++) {
                cout << i + 1 << " " << i + 1 << " ";
            }
            cout << endl;
            continue;
        }
        if (need == 1) {
            cout << "1 2 1 2 ";
            for (int i = 2; i < n; i++) {
                cout << i + 1 << " " << i + 1 << " ";
            }
            cout << endl;
            continue;
        }
        vector<int> ans(2 * n);
        ans[0] = 1, ans[2] = 1;
        int r;
        for (int i = 1, j = 2; j <= need; i += 2, j++) {
            ans[i] = j;
            ans[i + 3] = j;
            r = i + 3;
        }
        ans[r + 1] = need + 1;
        ans[r - 1] = need + 1;
        for (int i = 0; i <= r + 1; i++) {
            cout << ans[i] << " ";
        }
        for (int i = need + 2; i <= n; i++) {
            cout << i << " " << i << " ";
        }
        cout << endl;
    }

    return 0;
}
