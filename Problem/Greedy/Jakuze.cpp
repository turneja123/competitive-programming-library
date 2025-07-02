//https://olympicode.rs/problem/34
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int ans = 0;

void chk(int x, int y, int n, int m, vector<vector<int>> &a, vector<vector<int>> &bad) {
    ans -= bad[x][y];
    bad[x][y] = 1;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (abs(dx) + abs(dy) == 1 && x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && a[x + dx][y + dy] < a[x][y]) {
                bad[x][y] = 0;
            }
        }
    }
    ans += bad[x][y];
    return;
}


int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<int>> bad(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            chk(i, j, n, m, a, bad);
        }
    }
    if (ans == 1) {
        cout << "DA" << endl;
    } else {
        cout << "NE" << endl;
    }
    for (int k = 0; k < q; k++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--, y1--, x2--, y2--;
        swap(a[x1][y1], a[x2][y2]);
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) <= 1 && x1 + dx >= 0 && x1 + dx < n && y1 + dy >= 0 && y1 + dy < m) {
                    chk(x1 + dx, y1 + dy, n, m, a, bad);
                }
                if (abs(dx) + abs(dy) <= 1 && x2 + dx >= 0 && x2 + dx < n && y2 + dy >= 0 && y2 + dy < m) {
                    chk(x2 + dx, y2 + dy, n, m, a, bad);
                }
            }
        }
        if (ans == 1) {
            cout << "DA" << endl;
        } else {
            cout << "NE" << endl;
        }
    }
    return 0;
}

