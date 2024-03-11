//solution for https://cses.fi/problemset/task/1652
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

int a[N][N];
int pref[N][N];
int col[N][N];

void preprocess(int n) {
    pref[0][0] = a[0][0];
    col[0][0] = a[0][0];
    for (int i = 1; i < n; i++) {
        pref[0][i] = pref[0][i - 1] + a[0][i];
        col[0][i] = a[0][i];
    }
    for (int i = 1; i < n; i++) {
        pref[i][0] = pref[i - 1][0] + a[i][0];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            col[i][j] = col[i - 1][j] + a[i][j];
            pref[i][j] = pref[i][j - 1] + col[i][j];
        }
    }
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            if (c == '*')
                a[i][j] = 1;
        }
    }
    preprocess(n);
    for (int k = 0; k < q; k++) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        y1--, x1--, y2--, x2--;
        int sol = pref[y2][x2] - pref[y1 - 1][x2] - pref[y2][x1 - 1] + pref[y1 - 1][x1 - 1];
        cout << sol << endl;
    }
    return 0;

}
