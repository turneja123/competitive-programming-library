//https://www.spoj.com/problems/GEEKOUNT/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long dp[20][2][3];

long long calc(long long n) {
    if (n == 0) {
        return 0;
    }
    vector<int> a;
    while (n > 0) {
        a.push_back(n % 10);
        n /= 10;
    }
    reverse(a.begin(), a.end());
    for (int d = 1; d < 10; d++) {
        if (d < a[0]) {
            dp[0][d % 2][0] += 1;
        } else if (d == a[0]) {
            dp[0][d % 2][2] += 1;
        } else {
            dp[0][d % 2][1] += 1;
        }
    }
    for (int i = 1; i < a.size(); i++) {
        for (int d = 0; d < 10; d++) {
            if (d % 2 == 0) {
                if (d < a[i]) {
                    dp[i][0][0] += dp[i - 1][0][0] + dp[i - 1][1][0] + dp[i - 1][0][2] + dp[i - 1][1][2];
                    dp[i][0][1] += dp[i - 1][0][1] + dp[i - 1][1][1];
                } else if (d == a[i]) {
                    dp[i][0][0] += dp[i - 1][0][0] + dp[i - 1][1][0];
                    dp[i][0][2] += dp[i - 1][0][2] + dp[i - 1][1][2];
                    dp[i][0][1] += dp[i - 1][0][1] + dp[i - 1][1][1];

                } else {
                    dp[i][0][1] += dp[i - 1][0][1] + dp[i - 1][1][1] + dp[i - 1][0][2] + dp[i - 1][1][2];
                    dp[i][0][0] += dp[i - 1][0][0] + dp[i - 1][1][0];
                }
            } else {
                if (d < a[i]) {
                    dp[i][0][0] += dp[i - 1][0][0] + dp[i - 1][0][2];
                    dp[i][1][0] += dp[i - 1][1][0] + dp[i - 1][1][2];

                    dp[i][0][1] += dp[i - 1][0][1];
                    dp[i][1][1] += dp[i - 1][1][1];
                } else if (d == a[i]) {
                    dp[i][0][0] += dp[i - 1][0][0];
                    dp[i][1][0] += dp[i - 1][1][0];

                    dp[i][0][2] += dp[i - 1][0][2];
                    dp[i][1][2] += dp[i - 1][1][2];

                    dp[i][0][1] += dp[i - 1][0][1];
                    dp[i][1][1] += dp[i - 1][1][1];

                } else {
                    dp[i][0][1] += dp[i - 1][0][1] + dp[i - 1][0][2];
                    dp[i][1][1] += dp[i - 1][1][1] + dp[i - 1][1][2];

                    dp[i][0][0] += dp[i - 1][0][0];
                    dp[i][1][0] += dp[i - 1][1][0];
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < a.size(); i++) {
        ans += dp[i][0][0] + dp[i][0][2];
        if (i != a.size() - 1) {
            ans += dp[i][0][1];
        }
        for (int dx = 0; dx < 2; dx++) {
            for (int dy = 0; dy < 3; dy++) {
                dp[i][dx][dy] = 0;
            }
        }
    }
    return ans;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long l, r;
        cin >> l >> r;
        cout << calc(r) - calc(l - 1) << endl;
    }

    return 0;
}
