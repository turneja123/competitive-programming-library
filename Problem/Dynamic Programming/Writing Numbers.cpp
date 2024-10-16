//https://cses.fi/problemset/task/1086
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

long long dp[19][19][3];

long long calc(long long n, int dig) {
    vector<int> b;
    while (n > 0) {
        b.push_back(n % 10);
        n /= 10;
    }
    reverse(b.begin(), b.end());
    for (int i = 0; i < b.size(); i++) {
        for (int j = 0; j < 19; j++) {
            dp[i][j][0] = 0;
            dp[i][j][1] = 0;
            dp[i][j][2] = 0;
        }
    }
    for (int d = 1; d < 10; d++) {
        if (d < b[0]) {
            dp[0][d == dig][0]++;
        } else if (d == b[0]) {
            dp[0][d == dig][2]++;
        } else {
            dp[0][d == dig][1]++;
        }
    }

    for (int i = 1; i < b.size(); i++) {
        for (int j = 0; j < 19; j++) {
            for (int d = 0; d < 10; d++) {
                if (d == dig && j == 0) {
                    continue;
                }
                if (d < b[i]) {
                    dp[i][j][0] += dp[i - 1][j - (d == dig)][0] + dp[i - 1][j - (d == dig)][2];
                    dp[i][j][1] += dp[i - 1][j - (d == dig)][1];
                } else if (d == b[i]) {
                    dp[i][j][0] += dp[i - 1][j - (d == dig)][0];
                    dp[i][j][1] += dp[i - 1][j - (d == dig)][1];
                    dp[i][j][2] += dp[i - 1][j - (d == dig)][2];
                } else {
                    dp[i][j][1] += dp[i - 1][j - (d == dig)][1] + dp[i - 1][j - (d == dig)][2];
                    dp[i][j][0] += dp[i - 1][j - (d == dig)][0];
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < b.size(); i++) {
        for (int j = 1; j < 19; j++) {
            ans += (dp[i][j][0] + dp[i][j][2]) * j;
            if (i != b.size() - 1) {
                ans += dp[i][j][1] * j;
            }
        }
    }
    return ans;
}

int main() {
    IOS;
    long long n;
    cin >> n;
    long long l = 1, r = 1e18, ans = 1;
    while (l <= r) {
        long long mid = (l + r) / 2, mx = 0;
        for (int i = 0; i < 10; i++) {
            mx = max(mx, calc(mid, i));
        }
        if (mx <= n) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans;
    return 0;
}
