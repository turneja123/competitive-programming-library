//https://codeforces.com/contest/687/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;

int a[N];
bool dp[N][N][N];
bool exist[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    dp[0][0][0] = true;
    dp[0][a[0]][0] = true;
    dp[0][a[0]][a[0]] = true;
    exist[0] = true;
    exist[a[0]] = true;
    for (int i = 1; i < n; i++) {
        for (int j = m; j >= 0; j--) {
            for (int k = 0; k <= j; k++) {
                dp[i][j][k] |= dp[i - 1][j][k];
            }
            if (j >= a[i] && exist[j - a[i]]) {
                exist[j] = true;
                for (int k = 0; k <= j - a[i]; k++) {
                    dp[i][j][k] |= dp[i - 1][j - a[i]][k];
                    dp[i][j][k + a[i]] |= dp[i - 1][j - a[i]][k];
                }
            }
        }
    }
    int ans = 0;
    for (int k = 0; k <= m; k++) {
        if (dp[n - 1][m][k]) {
            ans++;
        }
    }
    cout << ans << endl;
    for (int k = 0; k <= m; k++) {
        if (dp[n - 1][m][k]) {
            cout << k << " ";
        }
    }
    return 0;
}
