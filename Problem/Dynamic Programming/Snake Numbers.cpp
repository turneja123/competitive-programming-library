//https://atcoder.jp/contests/abc387/tasks/abc387_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long dp[20][10][3];

long long calc(long long n) {
    vector<int> b;
    while (n > 0) {
        b.push_back(n % 10);
        n /= 10;
    }
    reverse(b.begin(), b.end());
    for (int d = 1; d < 10; d++) {
        if (d < b[0]) {
            dp[0][d][0] = 1;
        } else if (d == b[0]) {
            dp[0][d][2] = 1;
        } else {
            dp[0][d][1] = 1;
        }
    }
    for (int i = 1; i < b.size(); i++) {
        for (int j = 1; j < 10; j++) {
            for (int d = 0; d < j; d++) {
                if (d < b[i]) {
                    dp[i][j][0] += dp[i - 1][j][0] + dp[i - 1][j][2];
                    dp[i][j][1] += dp[i - 1][j][1];
                } else if (d == b[i]) {
                    dp[i][j][0] += dp[i - 1][j][0];
                    dp[i][j][1] += dp[i - 1][j][1];
                    dp[i][j][2] += dp[i - 1][j][2];
                } else {
                    dp[i][j][1] += dp[i - 1][j][1] + dp[i - 1][j][2];
                    dp[i][j][0] += dp[i - 1][j][0];
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < b.size(); i++) {
        for (int j = 1; j < 10; j++) {
            if (i < b.size() - 1) {
                ans += dp[i][j][0] + dp[i][j][1] + dp[i][j][2];
            } else {
                ans += dp[i][j][0] + dp[i][j][2];
            }
            dp[i][j][0] = 0, dp[i][j][1] = 0, dp[i][j][2] = 0;
        }
    }
    return ans;
}

int main() {
    IOS;
    long long l, r;
    cin >> l >> r;
    cout << calc(r) - calc(l - 1);
    return 0;
}
