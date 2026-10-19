//https://codeforces.com/contest/2273/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

int a[N][N];
int diff_x[N][N];
int diff_y[N][N];

int pref[N][N];

void calc_row(int i, int n) {
    if (i < 0 || i >= n) {
        return;
    }
    for (int j = 0; j < n; j++) {
        diff_y[i][j] = (i == 0 ? 0 : diff_x[i][j] != diff_x[i - 1][j]);
        pref[i][j] = (j == 0 ? 0 : pref[i][j - 1]) + diff_y[i][j];
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
                a[i][j] = -a[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int x;
                cin >> x;
                a[i][j] += x;
                diff_x[i][j] = (j == 0 ? 0 : a[i][j] - a[i][j - 1]);

            }
            calc_row(i, n);
        }
        while (q--) {
            char c;
            cin >> c;
            if (c == 'Q') {
                int x1, y1, x2, y2;
                cin >> x1 >> y1 >> x2 >> y2;
                x1--, y1--, x2--, y2--;
                string ans = "Yes";
                for (int i = x1 + 1; i <= x2; i++) {
                    if (pref[i][y2] - pref[i][y1] != 0) {
                        ans = "No";
                        break;
                    }
                }
                cout << ans << endl;
            } else {
                int x1, y1, x2, y2;
                cin >> x1 >> y1 >> x2 >> y2;
                x1--, y1--, x2--, y2--;
                int add;
                cin >> add;

                for (int i = x1; i <= x2; i++) {
                    if (y1 != 0) {
                        diff_x[i][y1] -= add;
                    }
                    if (y2 != n - 1) {
                        diff_x[i][y2 + 1] += add;
                    }
                }
                calc_row(x1, n);
                calc_row(x2 + 1, n);
            }
        }
    }

    return 0;
}
