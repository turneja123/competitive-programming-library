//https://dmoj.ca/problem/btoi13p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long dp[20][11][11][3];

long long calc(long long n) {
    if (n == -1) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    vector<int> b;
    while (n > 0) {
        b.push_back(n % 10);
        n /= 10;
    }
    reverse(b.begin(), b.end());
    for (int d = 1; d < 10; d++) {
        if (d < b[0]) {
            dp[0][10][d][0] = 1;
        } else if (d == b[0]) {
            dp[0][10][d][2] = 1;
        } else {
            dp[0][10][d][1] = 1;
        }
    }
    for (int i = 1; i < b.size(); i++) {
        for (int j = 0; j <= 10; j++) {
            for (int k = 0; k <= 10; k++) {
                for (int d = 0; d < 10; d++) {
                    if (j == k || j == d || k == d) {
                        continue;
                    }
                    if (d < b[i]) {
                        dp[i][k][d][0] += dp[i - 1][j][k][0] + dp[i - 1][j][k][2];
                        dp[i][k][d][1] += dp[i - 1][j][k][1];
                    } else if (d == b[i]) {
                        dp[i][k][d][0] += dp[i - 1][j][k][0];
                        dp[i][k][d][1] += dp[i - 1][j][k][1];
                        dp[i][k][d][2] += dp[i - 1][j][k][2];
                    } else {
                        dp[i][k][d][1] += dp[i - 1][j][k][1] + dp[i - 1][j][k][2];
                        dp[i][k][d][0] += dp[i - 1][j][k][0];
                    }
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < b.size(); i++) {
        for (int j = 0; j <= 10; j++) {
            for (int k = 0; k <= 10; k++) {
                if (i < b.size() - 1) {
                    ans += dp[i][j][k][0] + dp[i][j][k][1] + dp[i][j][k][2];
                } else {
                    ans += dp[i][j][k][0] + dp[i][j][k][2];
                }
                dp[i][j][k][0] = 0, dp[i][j][k][1] = 0, dp[i][j][k][2] = 0;
            }
        }
    }
    return ans + 1;
}

int main() {
    IOS;
    long long l, r;
    cin >> l >> r;
    cout << calc(r) - calc(l - 1);

    return 0;
}
