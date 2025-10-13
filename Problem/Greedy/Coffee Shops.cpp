//https://qoj.ac/contest/2539/problem/14430
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int n;
    cin >> n;
    if (n == 3 || n == 4) {
        int l = 1, r = 2 * n;
        for (int i = 0; i < n; i++) {
            int ans;
            if (i % 3 == 2) {
                ans = l++;
            } else {
                ans = r--;
            }
            cout << ans << " ";
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            cout << l++ << " ";
        }
    } else {
        vector<int> a(n, 0), b(n, 0);
        int l = 1, r = 2 * n;
        for (int i = 0; i + 1 < n; i += 2) {
            a[i] = l++;
            b[i + 1] = l++;
        }
        for (int i = 0; i < n; i++) {
            if (a[i] == 0) {
                a[i] = r--;
            }
            cout << a[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            if (b[i] == 0) {
                b[i] = r--;
            }
            cout << b[i] << " ";
        }

    }

    return 0;
}
