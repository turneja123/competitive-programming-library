//https://codeforces.com/contest/2219/problem/B2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        n = 2 * n + 1;

        int l = 1, r = n, L, M, R;
        while (l <= r) {
            int mid = (l + r) / 2;
            int m = mid;
            cout << "? " << mid << " ";
            for (int i = 1; i <= mid; i++) {
                cout << i << " ";
            }
            cout << endl;
            int x;
            cin >> x;
            if (m % 2 == x % 2) {
                l = mid + 1;
            } else {
                r = mid - 1;
                R = mid;
            }
        }
        l = 1, r = R;
        while (l <= r) {
            int mid = (l + r) / 2;
            int m = R - mid + 1;
            cout << "? " << m << " ";
            for (int i = mid; i <= R; i++) {
                cout << i << " ";
            }
            cout << endl;
            int x;
            cin >> x;
            if (m % 2 == x % 2) {
                r = mid - 1;
            } else {
                l = mid + 1;
                L = mid;
            }
        }
        l = L + 1, r = R - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int m = L + n - R + 1 + mid - L;
            cout << "? " << m << " ";
            for (int i = L + 1; i <= mid; i++) {
                cout << i << " ";
            }
            for (int i = 1; i <= L; i++) {
                cout << i << " ";
            }
            for (int i = R; i <= n; i++) {
                cout << i << " ";
            }
            cout << endl;
            int x;
            cin >> x;
            if (m % 2 == x % 2) {
                l = mid + 1;
            } else {
                r = mid - 1;
                M = mid;
            }
        }
        cout << "! " << L << " " << M << " " << R << endl;

    }
    return 0;
}
