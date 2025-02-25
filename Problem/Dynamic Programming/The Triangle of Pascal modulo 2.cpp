//https://www.spoj.com/problems/TRIMOD2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

long long pw[63];
long long dp[63][63][3];

long long calc(long long n) {
    vector<int> b;
    while (n > 0) {
        b.push_back(n % 2);
        n /= 2;
    }
    reverse(b.begin(), b.end());
    for (int i = 0; i < b.size(); i++) {
        for (int j = 0; j <= i + 1; j++) {
            dp[i][j][0] = 0;
            dp[i][j][1] = 0;
            dp[i][j][2] = 0;
        }
    }
    dp[0][1][2] = 1;
    for (int i = 1; i < b.size(); i++) {
        for (int j = 1; j <= i; j++) {
            if (b[i] == 0) {
                dp[i][j][0] += dp[i - 1][j][0];
                dp[i][j][1] += dp[i - 1][j][1];
                dp[i][j][2] += dp[i - 1][j][2];

                dp[i][j + 1][0] += dp[i - 1][j][0];
                dp[i][j + 1][1] += dp[i - 1][j][1] + dp[i - 1][j][2];
            } else {
                dp[i][j][0] += dp[i - 1][j][0] + dp[i - 1][j][2];
                dp[i][j][1] += dp[i - 1][j][1];

                dp[i][j + 1][0] += dp[i - 1][j][0];
                dp[i][j + 1][1] += dp[i - 1][j][1];
                dp[i][j + 1][2] += dp[i - 1][j][2];
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < b.size(); i++) {
        for (int j = 1; j <= i + 1; j++) {
            ans += (dp[i][j][0] + dp[i][j][2]) * pw[j];
            if (i != b.size() - 1) {
                ans += dp[i][j][1] * pw[j];
            }
        }
    }
    return ans;
}

int main() {
    //IOS;
    pw[0] = 1;
    for (int i = 1; i < 63; i++) {
        pw[i] = pw[i - 1] * 2;
    }
    long long n;
    while (cin >> n) {
        if (n == 0) {
            cout << 0 << endl;
            continue;
        }
        if (n == 1) {
            cout << 1 << endl;
            continue;
        }
        long long l = 1, r = 1000000000000, ans = r;
        while (l <= r) {
            long long mid = (l + r) / 2;
            long long cur = calc(mid - 1) + 1;
            if (cur >= n) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
