//https://lightoj.com/problem/intersection-of-cubes
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9;

int intersection(int n, vector<vector<int>> &v) {
    int xl = 0, yl = 0, zl = 0;
    int xr = INF, yr = INF, zr = INF;
    for (int i = 0; i < n; i++) {
        xl = max(xl, v[i][0]);
        yl = max(yl, v[i][1]);
        zl = max(zl, v[i][2]);
        xr = min(xr, v[i][3]);
        yr = min(yr, v[i][4]);
        zr = min(zr, v[i][5]);
    }
    if ((xr - xl) <= 0 || (yr - yl) <= 0 || (zr - zl) <= 0) {
        return 0;
    }
    return (xr - xl) * (yr - yl) * (zr - zl);
}

int main() {
    IOS;
    int t, ct = 0;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> v(n, vector<int>(6, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 6; j++) {
                cin >> v[i][j];
            }
        }
        cout << "Case " << ++ct << ": " << intersection(n, v) << endl;
    }

    return 0;
}
