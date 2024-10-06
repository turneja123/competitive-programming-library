//https://cses.fi/problemset/task/1739/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

int a[N][N];
int bit[N][N];

void update(int x, int y, int n, int m, int val){
    for (int i = x; i <= n; i += -i & i) {
        for (int j = y; j <= m; j += -j & j) {
            bit[i][j] += val;
        }
    }
}

int query(int x, int y){
    int sum = 0;
    for (int i = x; i > 0; i -= -i & i) {
        for (int j = y; j > 0; j -= -j & j) {
            sum += bit[i][j];
        }
    }
    return sum;
}

int calc(int x1, int y1, int x2, int y2) {
    int sum = query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
    return sum;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            if (c == '*') {
                a[i][j] = 1;
                update(i, j, n, n, 1);
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            if (a[x][y] == 1) {
                a[x][y] = 0;
                update(x, y, n, n, -1);
            } else {
                a[x][y] = 1;
                update(x, y, n, n, 1);
            }
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << calc(x1, y1, x2, y2) << endl;
        }
    }


    return 0;
}
