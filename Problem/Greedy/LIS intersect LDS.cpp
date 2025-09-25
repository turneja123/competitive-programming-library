//https://atcoder.jp/contests/arc206/tasks/arc206_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        if (n == k) {
            for (int i = 1; i <= n; i++) {
                cout << i << " ";
            }
            cout << endl;
        } else if (k > 1) {
            for (int i = n - k + 1; i <= n; i++) {
                cout << i << " ";
            }
            for (int i = n - k; i >= 1; i--) {
                cout << i << " ";
            }
            cout << endl;
        } else if (k == 1) {
            if (n < 5) {
                cout << -1 << endl;
            } else if (n == 5) {
                cout << "4 1 3 5 2" << endl;
            } else {
                cout << "5 2 4 ";
                for (int i = 6; i <= n; i++) {
                    cout << i << " ";
                }
                cout << "3 1" << endl;
            }
        } else {
            if (n < 8) {
                cout << -1 << endl;
            } else {
                int r = n / 2, l = r / 2;
                for (int i = l + r; i >= r + 1; i--) {
                    cout << i << " ";
                }
                for (int i = 1; i <= l; i++) {
                    cout << i << " ";
                }
                for (int i = l + r + 1; i <= n; i++) {
                    cout << i << " ";
                }
                for (int i = r; i >= l + 1; i--) {
                    cout << i << " ";
                }
                cout << endl;

            }
        }
    }

    return 0;
}
