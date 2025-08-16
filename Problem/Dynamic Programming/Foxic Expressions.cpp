//https://www.spoj.com/problems/UOFTAF/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;

int dp[N][N][2];

int calc(int i, int j, int n, int m, string &a, string &b, int f) {
    if (j == m) {
        return i == n || (i == n - 1 && !f) || (i == n - 2 && a[n - 1] == 'n');
    }
    if (i == n) {
        return f == 0 && j == m - 1;
    }
    if (dp[i][j][f] != -1) {
        return dp[i][j][f];
    }
    dp[i][j][f] = 0;
    if (f == 0) {
        if (i < n - 2 && a[i + 2] == 'n') {
            dp[i][j][f] |= calc(i + 3, j, n, m, a, b, 1);
            int J = j;
            while (J < m && b[J] == a[i]) {
                dp[i][j][f] |= calc(i + 3, J + 1, n, m, a, b, 1);
                J++;
            }
        }
        dp[i][j][f] |= calc(i, j + 1, n, m, a, b, 1);
        if (i == n - 1 || a[i + 1] != 'n') {
            dp[i][j][f] |= calc(i + 1, j + 1, n, m, a, b, 1);
            dp[i][j][f] |= calc(i + 1, j, n, m, a, b, 1);
            if (i != n - 1) {
                dp[i][j][f] |= calc(i + 2, j, n, m, a, b, 1);
                int J = j;
                while (J < m && b[J] == a[i]) {
                    dp[i][j][f] |= calc(i + 2, J + 1, n, m, a, b, 1);
                    J++;
                }
            }
            dp[i][j][f] |= calc(i + 1, j, n, m, a, b, 1);
            int J = j;
            while (J < m && b[J] == a[i]) {
                dp[i][j][f] |= calc(i + 1, J + 1, n, m, a, b, 1);
                J++;
            }
        } else {
            if (a[i] == b[j]) {
                dp[i][j][f] |= calc(i + 2, j + 2, n, m, a, b, 1);
            }
            int J = j;
            while (J < m && b[J] == b[j]) {
                dp[i][j][f] |= calc(i + 2, J + 1, n, m, a, b, 1);
                J++;
            }
        }
    }
    if (i < n - 1 && a[i + 1] == 'n') {
        dp[i][j][f] |= calc(i + 2, j, n, m, a, b, f);
        int J = j;
        while (J < m && b[J] == a[i]) {
            dp[i][j][f] |= calc(i + 2, J + 1, n, m, a, b, f);
            J++;
        }
    } else {
        if (a[i] == b[j]) {
            dp[i][j][f] |= calc(i + 1, j + 1, n, m, a, b, f);
        }
    }
    return dp[i][j][f];
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        string a, b;
        cin >> m >> b >> n >> a;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                dp[i][j][0] = -1;
                dp[i][j][1] = -1;
            }
        }
        calc(0, 0, n, m, a, b, 0);
        if (dp[0][0][0]) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}
