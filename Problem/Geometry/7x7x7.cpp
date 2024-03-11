//https://atcoder.jp/contests/abc343/tasks/abc343_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9;

int intersection(int n, vector<vector<int>> &v) {
    int xl = -2, yl = -2, zl = -2;
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
    int v1, v2, v3;
    cin >> v1 >> v2 >> v3;
    vector<int> c1{0, 0, 0, 7, 7, 7};
    for (int x2 = -2; x2 <= 9; x2++) {
        for (int y2 = -2; y2 <= 9; y2++) {
            for (int z2 = -2; z2 <= 9; z2++) {
                for (int x3 = -2; x3 <= 9; x3++) {
                    for (int y3 = -2; y3 <= 9; y3++) {
                        for (int z3 = -2; z3 <= 9; z3++) {
                            vector<int> c2{x2, y2, z2, x2 + 7, y2 + 7, z2 + 7};
                            vector<int> c3{x3, y3, z3, x3 + 7, y3 + 7, z3 + 7};
                            vector<vector<int>> v12{c1, c2};
                            vector<vector<int>> v13{c1, c3};
                            vector<vector<int>> v23{c2, c3};
                            vector<vector<int>> v123{c1, c2, c3};
                            int i12 = intersection(2, v12), i13 = intersection(2, v13),
                            i23 = intersection(2, v23), i123 = intersection(3, v123);
                            if (i123 == v3 && (i12 + i13 + i23 - 3 * i123) == v2 && (7 * 7 * 7 * 3 - 2 * i12 - 2 * i13 - 2 * i23 + 3 * i123) == v1) {
                                cout << "Yes" << endl;
                                cout << 0 << " " << 0 << " " << 0 << " " << x2 << " " << y2 << " " << z2 << " " << x3 << " " << y3 << " " << z3 << endl;
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "No" << endl;

    return 0;
}
