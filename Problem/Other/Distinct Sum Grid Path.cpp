//https://atcoder.jp/contests/arc214/tasks/arc214_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 14;

int a[N][N];
int n;


int go(int i, int j, int cur) {
    if (i == n - 1 && j == n - 1) {
        return 1;
    }

    int ct = 0;
    if (i == n - 1) {
        a[i][j + 1] = 0;
    } else {
        ct = go(i + 1, j, cur + a[i][j]);
        a[i][j + 1] = a[i + 1][j] + ct;
    }
    if (j != n - 1) {
        ct += go(i, j + 1, cur + a[i][j]);
    }
    return ct;
}

int main() {
    IOS;
    cin >> n;
    go(0, 0, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }


    return 0;
}
