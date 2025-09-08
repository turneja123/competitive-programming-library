//https://atcoder.jp/contests/arc205/tasks/arc205_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;

char c[N][N];
int a[N][N];
int pref[N][N];

void preprocess(int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pref[i][j] = a[i][j] + (i > 0 ? pref[i - 1][j] : 0) + (j > 0 ? pref[i][j - 1] : 0) - (i > 0 && j > 0 ? pref[i - 1][j - 1] : 0);
        }
    }
    return;
}

int query(int x1, int y1, int x2, int y2) {
    int ans = pref[x2][y2] - (x1 > 0 ? pref[x1 - 1][y2] : 0) - (y1 > 0 ? pref[x2][y1 - 1] : 0) + (x1 > 0 && y1 > 0 ? pref[x1 - 1][y1 - 1] : 0);
    return ans;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c[i][j];
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (c[i][j] == '.' && c[i + 1][j] == '.' && c[i][j + 1] == '.' && c[i + 1][j + 1] == '.') {
                a[i][j] = 1;
            } else {
                a[i][j] = 0;
            }
        }
    }
    preprocess(n, n);
    for (int k = 0; k < q; k++) {
        int x1, y1, x2, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        x1--, y1--, x2--, y2--;
        cout << query(x1, y1, x2 - 1, y2 - 1) << endl;
    }
    return 0;
}
