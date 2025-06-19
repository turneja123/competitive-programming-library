//https://dmoj.ca/problem/othscc4p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;

string a[N];

int l[N][N], r[N][N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int mn = N, b = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            l[i][j] = mn;
            if (a[i][j] == 'x') {
                mn = min(mn, j);
                b++;
            }
        }
    }
    if (b <= 1) {
        cout << 2 * n - 1;
        return 0;
    }
    int mx = -1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            r[i][j] = mx;
            if (a[i][j] == 'x') {
                mx = max(mx, j);
            }
        }
    }
    int ans = 0;
    int mxl = 0, mxr = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 'x') {
                ans++;
                if (l[i][j] > j) {
                    mxl = max(mxl, i + j);
                }
                if (r[i][j] < j) {
                    mxr = max(mxr, n - 1 - i + n - 1 - j);
                }
            } else {
                if (l[i][j] <= j && r[i][j] >= j) {
                    ans++;
                }
                if (l[i][j] > j && r[i][j] >= j) {
                    mxl = max(mxl, i + j + 1);
                }
                if (r[i][j] < j && l[i][j] <= j) {
                    mxr = max(mxr, n - 1 - i + n - 1 - j + 1);
                }
            }
        }
    }
    cout << ans + mxl + mxr;
    return 0;
}
