//https://codeforces.com/contest/2161/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;

char a[N][N];

int calc(int dx, int dy, int n, int x, int y, int f, int z) {
    int t = 0, ct = 0;
    vector<pair<int, int>> restore;
    while (x >= 0 && y >= 0 && x < n && y < n) {
        if (a[x][y] == '#') {
            ct++;
        }
        if (t == f) {
            x += dx;
        } else {
            y += dy;
        }
        t = (t + 1) % 2;
    }
    int ans = z == ct;
    return ans;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int ans = 0;
        int z = 0;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < n; j++) {
                a[i][j] = s[j];
                if (a[i][j] == '#') {
                    z++;
                }
            }
        }
        if (z == 0) {
            cout << "YES" << endl;
            continue;
        }
        if (z == 4) {
            int edge = 0;
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - 1; j++) {
                    if (a[i][j] == '#' && a[i][j + 1] == '#' && a[i + 1][j] == '#' && a[i + 1][j + 1] == '#') {
                        edge = 1;
                    }
                }
            }
            if (edge) {
                cout << "YES" << endl;
                continue;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] == '#') {
                    int x, y;
                    x = i, y = j;
                    ans |= calc(1, -1, n, x, y, 0, z);
                    ans |= calc(1, 1, n, x, y, 0, z);
                    ans |= calc(-1, 1, n, x, y, 0, z);
                    ans |= calc(-1, -1, n, x, y, 0, z);
                    ans |= calc(1, -1, n, x, y, 1, z);
                    ans |= calc(1, 1, n, x, y, 1, z);
                    ans |= calc(-1, 1, n, x, y, 1, z);
                    ans |= calc(-1, -1, n, x, y, 1, z);
                }
            }
        }
        if (ans) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
