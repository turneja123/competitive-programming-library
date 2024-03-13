//https://atcoder.jp/contests/arc173/tasks/arc173_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long dp[18][10][2];

long long calc(long long a) {
    for (int i = 0; i <= 9; i++) {
        dp[0][i][0] = 0;
        dp[0][i][1] = 0;
    }
    long long ans = 0;
    for (int i = 0; i <= 9; i++) {
        int c = a % 10;
        if (i <= c) {
            dp[0][i][0]++;
            if (i != 0) {
                ans++;
            }
        } else {
            dp[0][i][1]++;
            if (a > 9 && i != 0) {
                ans++;
            }
        }
    }
    a /= 10;
    for (int i = 1; a > 0; i++) {
        int c = a % 10;
        for (int j = 0; j < 10; j++) {
            dp[i][j][0] = 0;
            dp[i][j][1] = 0;
            for (int cif = 0; cif <= 9; cif++) {
                if (j == cif) {
                    continue;
                }
                if (j < c) {
                    dp[i][j][0] = dp[i][j][0] + dp[i - 1][cif][0];
                    dp[i][j][0] = dp[i][j][0] + dp[i - 1][cif][1];
                    if (j > 0) {
                        ans = ans + dp[i - 1][cif][0];
                        ans = ans + dp[i - 1][cif][1];
                    }
                } else if (j > c) {
                    dp[i][j][1] = dp[i][j][1] + dp[i - 1][cif][0];
                    dp[i][j][1] = dp[i][j][1] + dp[i - 1][cif][1];
                    if (a > 9 && j > 0) {
                        ans = ans + dp[i - 1][cif][0];
                        ans = ans + dp[i - 1][cif][1];
                    }
                } else {
                    dp[i][j][0] = dp[i][j][0] + dp[i - 1][cif][0];
                    dp[i][j][1] = dp[i][j][1] + dp[i - 1][cif][1];
                    if (j > 0) {
                        ans = ans + dp[i - 1][cif][0];
                        if (a > 9) {
                            ans = ans + dp[i - 1][cif][1];
                        }
                    }
                }
            }
        }
        a /= 10;
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long k;
        cin >> k;
        long long l = 1, r = 1e18, ans = r;
        while (l <= r) {
            long long mid = (l + r) / 2;
            long long ct = calc(mid);
            if (ct >= k) {
                if (ct == k) {
                    ans = min(ans, mid);
                }
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
