//https://www.spoj.com/problems/PYTRIP2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<vector<int>> mat{{1,-2,2,2,-1,2,2,-2,3}, {1,2,2,2,1,2,2,2,3}, {-1,2,2,-2,1,2,-2,2,3}};

int k = 0;

void go(int a, int b, int c, int n, int m) {
    if (c > m) {
        return;
    }
    int x = min({a, b, c});
    int y = max({a, b, c});
    int l, r;
    if (x >= n) {
        l = 1;
    } else {
        l = (n + x - 1) / x;
    }
    r = m / y;
    k += max(0, r - l + 1);
    for (int i = 0; i < 3; i++) {
        int A = mat[i][0] * a + mat[i][1] * b + mat[i][2] * c;
        int B = mat[i][3] * a + mat[i][4] * b + mat[i][5] * c;
        int C = mat[i][6] * a + mat[i][7] * b + mat[i][8] * c;
        go(A, B, C, n, m);
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        k = 0;
        int n, m;
        cin >> n >> m;
        go(3, 4, 5, n, m);
        cout << k << endl;
    }
    return 0;
}
