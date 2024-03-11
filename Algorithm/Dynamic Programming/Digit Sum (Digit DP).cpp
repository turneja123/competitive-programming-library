//https://www.spoj.com/problems/PR003004/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 17;

long long dp[N][2];
long long ct[N][2];

long long calc(long long a) {
    if (a < 10) {
        return a * (a + 1) / 2;
    }
    long long ans = 0;
    dp[0][0] = 0;
    dp[0][1] = 0;
    ct[0][0] = 0;
    ct[0][1] = 0;
    for (int k = 0; k < 10; k++) {
        if (k <= a % 10) {
            dp[0][0] += k;
            ct[0][0] += 1;
            ans += k;
        } else {
            dp[0][1] += k;
            ct[0][1] += 1;
            ans += k;
        }
    }
    a /= 10;
    for (int i = 1; a > 0; i++) {
        dp[i][0] = 0;
        dp[i][1] = 0;
        ct[i][0] = 0;
        ct[i][1] = 0;
        for (long long k = 0; k < 10; k++) {
            if (k < a % 10) {
                ct[i][0] += ct[i - 1][0];
                ct[i][0] += ct[i - 1][1];

                dp[i][0] += k * ct[i - 1][0] + dp[i - 1][0];
                dp[i][0] += k * ct[i - 1][1] + dp[i - 1][1];
                if (k != 0) {
                    ans += k * ct[i - 1][0] + dp[i - 1][0];
                    ans += k * ct[i - 1][1] + dp[i - 1][1];
                }
            } else if (k == a % 10) {
                ct[i][0] += ct[i - 1][0];
                ct[i][1] += ct[i - 1][1];

                dp[i][0] += k * ct[i - 1][0] + dp[i - 1][0];
                dp[i][1] += k * ct[i - 1][1] + dp[i - 1][1];
                if (k != 0) {
                    ans += k * ct[i - 1][0] + dp[i - 1][0];
                    if (a > 9) {
                        ans += k * ct[i - 1][1] + dp[i - 1][1];
                    }
                }
            } else {
                ct[i][1] += ct[i - 1][0];
                ct[i][1] += ct[i - 1][1];

                dp[i][1] += k * ct[i - 1][0] + dp[i - 1][0];
                dp[i][1] += k * ct[i - 1][1] + dp[i - 1][1];
                if (k != 0) {
                    if (a > 9) {
                        ans += k * ct[i - 1][0] + dp[i - 1][0];
                        ans += k * ct[i - 1][1] + dp[i - 1][1];
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
        long long a, b;
        cin >> a >> b;
        cout << (long long)(calc(b) - calc(a - 1)) << endl;
    }
    return 0;
}
