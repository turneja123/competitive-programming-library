//https://atcoder.jp/contests/abc366/tasks/abc366_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;

int a[N][N][N];
int pref[N][N][N];

void preprocess(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                pref[i][j][k] = a[i][j][k] + (i > 0 ? pref[i - 1][j][k] : 0) + (j > 0 ? pref[i][j - 1][k] : 0) + (k > 0 ? pref[i][j][k - 1] : 0)
                - (i > 0 && j > 0 ? pref[i - 1][j - 1][k] : 0) - (i > 0 && k > 0 ? pref[i - 1][j][k - 1] : 0) - (j > 0 && k > 0 ? pref[i][j - 1][k - 1] : 0)
                + (i > 0 && j > 0 && k > 0 ? pref[i - 1][j - 1][k - 1] : 0);
            }
        }
    }
    return;
}

int query(int x1, int x2, int y1, int y2, int z1, int z2) {
    int ans = pref[x2][y2][z2] - (x1 > 0 ? pref[x1 - 1][y2][z2] : 0) - (y1 > 0 ? pref[x2][y1 - 1][z2] : 0) - (z1 > 0 ? pref[x2][y2][z1 - 1] : 0)
    + (x1 > 0 && y1 > 0 ? pref[x1 - 1][y1 - 1][z2] : 0) + (x1 > 0 && z1 > 0 ? pref[x1 - 1][y2][z1 - 1] : 0) + (y1 > 0 && z1 > 0 ? pref[x2][y1 - 1][z1 - 1] : 0)
    - (x1 > 0 && y1 > 0 && z1 > 0 ? pref[x1 - 1][y1 - 1][z1 - 1] : 0);
    return ans;
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                cin >> a[i][j][k];
            }
        }
    }
    preprocess(n);
    cin >> q;
    for (int k = 0; k < q; k++) {
        int x1, x2, y1, y2, z1, z2;
        cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;
        x1--, x2--, y1--, y2--, z1--, z2--;
        cout << query(x1, x2, y1, y2, z1, z2) << endl;
    }
    return 0;

}
