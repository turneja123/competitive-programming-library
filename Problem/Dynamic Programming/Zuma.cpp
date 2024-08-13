//https://codeforces.com/contest/608/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;

int a[N];
int dp[N][N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            if (i == 0) {
                dp[j][j] = 1;
                continue;
            }
            dp[j][j + i] = 1 + dp[j + 1][j + i];
            if (a[j] == a[j + 1]) {
                dp[j][j + i] = 1 + dp[j + 2][j + i];
            }
            for (int k = j + 2; k <= j + i; k++) {
                if (a[j] == a[k]) {
                    dp[j][j + i] = min(dp[j][j + i], dp[j + 1][k - 1] + dp[k + 1][j + i]);
                }
            }
        }
    }
    cout << dp[0][n - 1] << endl;
    return 0;
}
